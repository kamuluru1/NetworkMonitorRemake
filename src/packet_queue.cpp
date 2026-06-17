#include <iostream>
#include <optional>
#include <mutex>
#include <queue>
#include <condition_variable>

#include "packet_queue.hpp"
#include "packet.hpp"


PacketQueue::PacketQueue(size_t capacity) : capacity_(capacity) {}
PacketQueue::~PacketQueue() {}

bool PacketQueue::enqueue(Packet&& packet) {
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

std::optional<Packet> PacketQueue::dequeue() {
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, [this]{ return !buffer_.empty() || done_; });

    if (buffer_.empty()) return std::nullopt;

    Packet pkt = std::move(buffer_.front());
    buffer_.pop();

    return pkt;
}

void PacketQueue::shutdown() {

    {
        std::lock_guard<std::mutex> lock(mtx_);
        done_ = true;
    }

    cv_.notify_all();
}

size_t PacketQueue::get_capacity() {
    return capacity_;
}

void PacketQueue::set_capacity(size_t capacity) {
    capacity_ = capacity;
}
