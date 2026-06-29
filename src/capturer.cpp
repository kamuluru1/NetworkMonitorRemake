#pragma once
#include <iostream>
#include <pcap.h>

#include "packet_queue.hpp"
#include "capturer.hpp"
#include "packet.hpp"

Capturer::Capturer(const std::string& device, PacketQueue& packet_queue) : packet_queue_(packet_queue), active_(false) {
    char errbuf[PCAP_ERRBUF_SIZE];
    handle_ = pcap_open_live(device.c_str(), 65535, 1, 100, errbuf);
    if (handle_ == nullptr) {
        throw std::runtime_error("pcap_open_live failed: " + std::string(errbuf));
    }
}
Capturer::~Capturer() {}

void Capturer::capture() {
    struct pcap_pkthdr* header;
    const u_char* data;
    while (active_) {
        int rc = pcap_next_ex(handle_, &header, &data);
        switch (rc) {
            case 1: {
                Packet packet = to_packet(header, data);
                captured_++;
                packet_queue_.enqueue(std::move(packet));
                break;
            }
            case 0: {
                break;
            }
            case -1: {
                break;
            }
            case -2: {
                break;
            }
        }

    }
}

Packet Capturer::to_packet(const pcap_pkthdr* header, const u_char* data) {

}

void Capturer::activate() {
    active_ = true;
}

void Capturer::stop() {
    active_ = false;
}

