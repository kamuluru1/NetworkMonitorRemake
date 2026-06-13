#include <iostream>
#include <chrono>

using namespace std;

struct Packet {
    chrono::milliseconds ts; // Timestamp
    uint32_t wire_length;
    vector<uint8_t> data; // Bits

};