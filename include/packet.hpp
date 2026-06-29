#pragma once
#include <iostream>
#include <chrono>
#include <vector>
#include <cstdint>

using namespace std;

struct Packet {
    chrono::microseconds ts; // Timestamp
    uint32_t wire_length;
    vector<uint8_t> data; // Bits
};