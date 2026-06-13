#include <iostream>
#include <packet.hpp>
#include <optional>
#include <mutex>
#include <queue>
#include <condition_variable>

class PacketQueue {
private:
    std::queue<Packet> buffer_;
    size_t capacity_;
    uint64_t dropped_ = 0;
    std::mutex mtx_;
    std::condition_variable cv_;
    bool done_ = false;

public:

    PacketQueue(size_t capacity) : capacity_(capacity) {}
    ~PacketQueue() {}

    bool enqueue(Packet&& packet) {
        std::lock_guard<std::mutex> lock(mtx_);

        if (buffer_.size() < capacity_) {
            buffer_.push(std::move(packet));
            return true;
        }
        else {
            dropped_++;
            return false;
        }

        cv_.notify_one();
    }

    std::optional<Packet> dequeue() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]{ return !buffer_.empty() || done_; });

        if (buffer_.empty()) return std::nullopt;

        Packet pkt = std::move(buffer_.front());
        buffer_.pop();

        return pkt;

    }

    void shutdown() {
        done_ = true;
        cv_.notify_all();
    }

    size_t get_capacity() {
        return capacity_;
    }

    void set_capacity(size_t capacity) {
        capacity_ = capacity;
    }
};
