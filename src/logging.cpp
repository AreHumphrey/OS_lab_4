#include "logging.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

namespace lab4 {

std::string format_line(const Sample& s) {
    auto ms_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
        s.ts.time_since_epoch()
    ).count();
    
    std::ostringstream oss;
    oss << ms_epoch << ';' 
        << iso_time(s.ts) << ';' 
        << std::fixed << std::setprecision(2) << s.value;
    return oss.str();
}

std::optional<std::int64_t> parse_epoch_ms(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    if (!std::getline(iss, token, ';')) return std::nullopt;
    try {
        return std::stoll(token);
    } catch (...) {
        return std::nullopt;
    }
}

void append_line(const std::string& path, const std::string& line) {
    std::ofstream out(path, std::ios::app);
    if (out.is_open()) {
        out << line << '\n';
        out.flush();
    }
}

void prune_log(const std::string& path, std::int64_t cutoff_ms) {
    std::ifstream in(path);
    if (!in.is_open()) return;
    
    std::vector<std::string> keep;
    std::string line;
    while (std::getline(in, line)) {
        auto ms = parse_epoch_ms(line);
        if (ms && *ms >= cutoff_ms) {
            keep.push_back(line);
        }
    }
    in.close();
    
    std::ofstream out(path, std::ios::trunc);
    if (out.is_open()) {
        for (const auto& l : keep) {
            out << l << '\n';
        }
        out.flush();
    }
}

}  // namespace lab4
