#include <parser.hpp>

#include <algorithm>
#include <charconv>
#include <iostream>

uint32_t Parser::ReadGuardId(const std::string &line) {
  auto begin_pos = line.find_first_of('#');
  auto end_pos = line.find_first_of(' ', begin_pos);
  int guard_id = 0;
  std::from_chars(line.data() + begin_pos + 1, line.data() + end_pos, guard_id);
  return static_cast<uint32_t>(guard_id);
}

void Parser::AddLine(const std::string &str) {
  uint32_t timestamp = 0;
  std::from_chars(str.data() + 15, str.data() + 17, timestamp);

  if (IsAsleep(str)) {
    guards_[last_guard_].Sleep(timestamp);
  }

  else if (IsAwake(str)) {
    guards_[last_guard_].Awake(timestamp);
  }

  else if (IsNewShift(str)) {
    last_guard_ = ReadGuardId(str);
    guards_[last_guard_].BeginShift();
  }
}

bool Parser::IsNewShift(const std::string& line) {
  return ContainsSubstring(line, "Guard");
}

bool Parser::IsAsleep(const std::string& line) {
  return ContainsSubstring(line, "falls asleep");
}


bool Parser::IsAwake(const std::string& line) {
  return ContainsSubstring(line, "wakes up");
}

bool Parser::ContainsSubstring(const std::string& line, std::string_view substr) {
  return line.find(substr) != std::string::npos;
}

std::pair<uint32_t, Guard> Parser::GetMostSleeping() {
  return *std::max_element(
      guards_.begin(), guards_.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.second.CountSleepingTime() < rhs.second.CountSleepingTime();
      });
}

std::pair<uint32_t, uint32_t> Parser::GetMostPropableHour() {
  uint32_t best_hour = 0;
  const auto [id, guard] = *std::max_element(
      guards_.begin(), guards_.end(),
      [&best_hour](const auto &lhs, const auto &rhs) mutable {
        const auto [lhs_probability, lhs_timestamp] = lhs.second.GetMostPropableHour();
        const auto [rhs_probability, rhs_timestamp] = rhs.second.GetMostPropableHour();
        if(lhs_probability < rhs_probability) {
          best_hour = rhs_timestamp;
          return true;
        }
        best_hour = lhs_timestamp;
        return false;
      });

  guard.Print();
  return {id, best_hour};
}
