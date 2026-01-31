#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace lab4 {

using Clock = std::chrono::system_clock;
using TimePoint = Clock::time_point;

inline std::int64_t now_ms() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(Clock::now().time_since_epoch()).count();
}

std::string iso_time(const TimePoint& tp);

std::string data_dir();
std::string measurements_log_path();  
std::string hourly_log_path();       
std::string daily_log_path();       

}  // namespace lab4
