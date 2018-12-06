#include <parser.hpp>

#include <charconv>
#include <iterator>
#include <sstream>
#include <utility>
#include <vector>
#include <iostream>

Claim Parser::ParseClaim(const std::string &s) {
  std::istringstream iss(s);
  std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());
  size_t id = Parser::ParseId(results[0]);
  auto [x, y] = Parser::ParseXY(results[2]);
  auto [cols, rows] = Parser::ParseRowCols(results[3]);
  return {id, rows, cols, x, y};
}

size_t Parser::ParseId(std::string_view s) {
  size_t id{0};
  std::from_chars(s.data() + 1, s.data() + s.size(), id);
  return id;
}

std::pair<size_t, size_t> Parser::ParseXY(std::string_view s) {
  return ParseNumbers(s, ',');
}

std::pair<size_t, size_t> Parser::ParseRowCols(std::string_view s) {
  return ParseNumbers(s, 'x');
}

std::pair<size_t, size_t> Parser::ParseNumbers(std::string_view s, char delim) {
  auto comma_pos = s.find(delim);
  size_t x{0};
  size_t y{0};
  std::from_chars(s.data(), s.data() + comma_pos, x);
  std::from_chars(s.data() + comma_pos + 1, s.data() + s.size(), y);
  return {x, y};
}
