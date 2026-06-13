#pragma once
#include <iostream>
#include <packet.hpp>
#include <optional>


class PacketQueue {
private:
    std::queue<Packet> buffer_;
    size_t capacity_;
    uint64_t dropped_ = 0;
    std::mutex mtx_;
    std::condition_variable cv_;
    bool done_ = false;

public:
    PacketQueue();
    void enqueue(Packet&& packet);
    std::optional<Packet> dequeue();
    void shutdown();
    size_t get_cpacity();
    void set_capacity(size_t capacity);
};
