#pragma once

#include <optional>
#include <string>

#include "common.h"
#include "sample.h"

namespace lab4 {

// Форматирование измерения в строку для лога
std::string format_line(const Sample& s);

// Парсинг временной метки из строки лога
std::optional<std::int64_t> parse_epoch_ms(const std::string& line);

// Добавление строки в конец файла
void append_line(const std::string& path, const std::string& line);

// Очистка лога: удаление записей старше cutoff_ms
void prune_log(const std::string& path, std::int64_t cutoff_ms);

}  // namespace lab4
