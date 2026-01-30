#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace lab4 {

using Clock = std::chrono::system_clock;
using TimePoint = Clock::time_point;

// Текущее время в миллисекундах с эпохи
inline std::int64_t now_ms() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(Clock::now().time_since_epoch()).count();
}

// ISO timestamp для логов
std::string iso_time(const TimePoint& tp);

// Пути к файлам логов
std::string data_dir();
std::string measurements_log_path();  // Все измерения (24 часа)
std::string hourly_log_path();        // Среднее по часам (30 дней)
std::string daily_log_path();         // Среднее по дням (текущий год)

}  // namespace lab4
