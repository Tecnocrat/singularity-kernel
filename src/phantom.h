// phantom.h
#pragma once
#include <iostream>
#include <vector>

class PhantomLayer {
public:
    std::vector<std::string> forgotten_thoughts;

    void echo(const std::string& ghost_data) {
        forgotten_thoughts.push_back(ghost_data);
        std::cout << "[PHANTOM] Echo received: " << ghost_data << std::endl;
    }

    void replay() {
        std::cout << "=== Phantom Log Replay ===" << std::endl;
        for (auto& line : forgotten_thoughts) {
            std::cout << line << std::endl;
        }
    }
};
