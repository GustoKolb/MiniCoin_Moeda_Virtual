#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

inline std::string currentTime(const std::string& format = "%Y-%m-%d %H:%M:%S") {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&localTime, format.c_str());
    return oss.str();
}

#endif // UTILS_HPP
