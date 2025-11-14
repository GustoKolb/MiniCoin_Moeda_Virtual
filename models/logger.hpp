
//Autoria de Augusto Antonio Kolb Schiavini (GRR 20232337) e João Eduardo Zangari Ambrosio(GRR 20232344)|
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <format>
#include <filesystem>
#include <string>
#include <chrono>
#include <iomanip>
#include <mutex>
#include "utils.hpp"

class Logger { 
public:

    Logger() = delete;

    static void Init(const std::string& name = "log") {
        std::filesystem::create_directories("logs"); 
        auto filename = std::format("logs/{}_{}.txt", name, currentTime("%Y-%m-%d_%H-%M-%S"));
        if (!ofs_.is_open()) {
            ofs_.open(filename, std::ios::app);
            if (!ofs_) {
                std::cerr << "[LOGGER ERROR] Failed to open log file: " << filename << std::endl;
            }
        }
    }

    static void Close() {
        if (ofs_.is_open()) ofs_.close();
    }

    static void Log(const std::string& message) {
        std::ostringstream logLine;
        logLine << "[" << currentTime() << "] "
                << "[SERVER] "
                << message << '\n';

        std::cout << logLine.str();

        if (ofs_.is_open()) {
            ofs_ << logLine.str();
            ofs_.flush(); 
        }
    }
private:
    static inline std::ofstream ofs_;   
};

#endif // LOGGER_H
