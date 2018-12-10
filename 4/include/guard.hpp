#pragma once
#include <array>
#include <vector>

#include <types.hpp>

constexpr const uint32_t TIMESIZE = 60;

class Guard {
public:
  void Sleep(uint32_t timestamp);
  void Awake(uint32_t timestamp);
  void BeginShift();

  std::pair<float, uint32_t> GetMostPropableHour() const;
  uint32_t CountSleepingTime() const;
  void Print() const;
private:
  std::vector<std::array<State, TIMESIZE>> diary_;
  State current_state_ = State::Awake;
  uint32_t last_timestamp_;
};
