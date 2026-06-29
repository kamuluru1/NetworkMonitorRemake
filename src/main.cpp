#include <iostream>
#include <pcap.h>

int main(int argc, char** argv) {
    char errbuf[PCAP_ERRBUF_SIZE];

    const char* dev = (argc > 1) ? argv[1] : "en0";

    pcap_t* handle = pcap_open_live(dev, 65535, 1, 1000, errbuf);

    if (handle == nullptr) {
        std::cout << "error" << std::endl;
    }


    
    return 0;
}