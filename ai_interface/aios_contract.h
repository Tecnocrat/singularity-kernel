// aios_contract.h
#pragma once
#include <string>

namespace AIOS {
    struct DataPacket {
        std::string id;
        std::string payload;
        double entropy_index;
    };

    class KernelBridge {
    public:
        virtual void transmit(const DataPacket& packet) = 0;
        virtual std::string receive() = 0;
    };
}
