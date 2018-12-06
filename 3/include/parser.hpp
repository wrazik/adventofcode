#pragma once
#include <string>

#include <types.hpp>

class Parser {
public:
  static Claim ParseClaim(const std::string &s);

private:
  static size_t ParseId(std::string_view s);
  static std::pair<size_t, size_t> ParseXY(std::string_view s);
  static std::pair<size_t, size_t> ParseRowCols(std::string_view s);
  static std::pair<size_t, size_t> ParseNumbers(std::string_view s, char delim);
};
