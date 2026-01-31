#include "common.h"


#include <filesystem>

#include <iomanip>

#include <sstream>


#ifdef _WIN32

#define NOMINMAX

#include <windows.h>

#else

#include <unistd.h>

#endif


namespace fs = std::filesystem;

namespace lab4 {

std::string iso_time(const TimePoint& tp) {
    using namespace std::chrono;
    auto tt = Clock::to_time_t(tp);
    std::tm tm{};
#ifdef _WIN32

    localtime_s(&tm, &tt);
#else

    localtime_r(&tt, &tm);
#endif

    auto ms = duration_cast<milliseconds>(tp.time_since_epoch()) % 1000;
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") 
        << '.' << std::setw(3) << std::setfill('0') << ms.count();
    return oss.str();
}

std::string data_dir() {
  
    fs::path exe_path;
#ifdef _WIN32

    char buffer[MAX_PATH];
    DWORD len = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    exe_path = std::string(buffer, buffer + len);
#else

    char buffer[4096];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len > 0) {
        buffer[len] = '\0';
        exe_path = std::string(buffer);
    } else {
        exe_path = fs::current_path() / "build" / "lab4_main";
    }
#endif


   
    fs::path project_root = exe_path.parent_path();
    int attempts = 0;
    while (attempts < 5 && !fs::exists(project_root / "CMakeLists.txt")) {
        project_root = project_root.parent_path();
        attempts++;
    }
    
    if (!fs::exists(project_root / "CMakeLists.txt")) {
   
        project_root = fs::current_path();
    }
    
    fs::path logs_dir = project_root / "logs";
    std::error_code ec;
    fs::create_directories(logs_dir, ec);
    
    return project_root.string();
}

std::string measurements_log_path() {
    return (fs::path(data_dir()) / "logs" / "measurements.log").string();
}

std::string hourly_log_path() {
    return (fs::path(data_dir()) / "logs" / "hourly_avg.log").string();
}

std::string daily_log_path() {
    return (fs::path(data_dir()) / "logs" / "daily_avg.log").string();
}

}  // namespace lab4
