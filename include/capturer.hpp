#pragma once
#include <pcap.h>

#include "packet_queue.hpp"

class Capturer {
private:
    PacketQueue& packet_queue_;
    pcap_t* handle_ = nullptr;
    uint64_t captured_ = 0; // Keeps track of how many packets are captured
    std::atomic<bool> active_; // Keeps track if the capturer is turned on or off

public:
    Capturer(const std::string& device_, PacketQueue& packet_queue);
    ~Capturer();

    void capture();
    Packet to_packet(const pcap_pkthdr* header, const u_char* data);
    void activate();
    void stop();
};