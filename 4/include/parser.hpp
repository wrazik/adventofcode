#pragma once
#include <string>
#include <unordered_map>

#include <guard.hpp>

class Parser {
public:
  void AddLine(const std::string &line);
  std::pair<uint32_t, uint32_t> GetMostFrequentHour();
  std::pair<uint32_t, Guard> GetMostSleeping();

private:
  static bool IsNewShift(const std::string &line);
  static bool IsAsleep(const std::string &line);
  static bool IsAwake(const std::string &line);
  static bool ContainsSubstring(const std::string &line,
                                std::string_view substr);

  static uint32_t ReadGuardId(const std::string &line);
  std::unordered_map<uint32_t, Guard> guards_;
  uint32_t last_guard_ = 0;
  };
