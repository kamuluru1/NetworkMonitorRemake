#pragma once
#include <iostream>
#include <optional>

#include "packet.hpp"


class PacketQueue {
private:
    std::queue<Packet> buffer_;
    size_t capacity_;
    uint64_t dropped_ = 0;
    std::mutex mtx_;
    std::condition_variable cv_;
    bool done_ = false;

public:
    PacketQueue(size_t capacity);
    ~PacketQueue();
    bool enqueue(Packet&& packet);
    std::optional<Packet> dequeue();
    void shutdown();
    size_t get_capacity();
    void set_capacity(size_t capacity);
};
