#include <guard.hpp>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>

void Guard::Sleep(uint32_t timestamp) {
  using namespace std::string_literals;
  if (timestamp > TIMESIZE)
    throw std::runtime_error("Invalid timestamp:"s + std::to_string(timestamp));
  if (current_state_ != State::Awake)
    throw std::runtime_error("Cannot go sleep, guard wasn't awake!");
  current_state_ = State::Sleep;
  last_timestamp_ = timestamp;
}

void Guard::Awake(uint32_t timestamp) {
  if (current_state_ != State::Sleep)
    throw std::runtime_error("Cannot awake, guard wasn't sleepint!");

  auto begin = diary_.back().begin() + last_timestamp_;
  auto end = diary_.back().begin() + timestamp;
  std::fill(begin, end, State::Sleep);
  current_state_ = State::Awake;
  last_timestamp_ = timestamp;
}

std::pair<uint32_t, uint32_t> Guard::GetMostFrequentHour() const {
  std::array<uint32_t, TIMESIZE> quantity;
  quantity.fill(0);
  for (uint32_t i = 0; i < TIMESIZE; ++i) {
    auto count =
        std::count_if(diary_.begin(), diary_.end(),
                      [i](const auto &row) { return row[i] == State::Sleep; });
    quantity[i] = count;
  }

  auto max = std::max_element(quantity.begin(), quantity.end());
  return {*max, std::distance(quantity.begin(), max)};
}

uint32_t Guard::CountSleepingTime() const {
  return std::accumulate(
      diary_.begin(), diary_.end(), 0u, [](uint32_t prev, const auto &row) {
        return prev + std::count(row.begin(), row.end(), State::Sleep);
      });
}

void Guard::BeginShift() {
  std::array<State, TIMESIZE> day_;
  day_.fill(State::Awake);
  diary_.push_back(std::move(day_));
}

void Guard::Print() const{
  int counter = 0;
  std::cout << "\t";
  for (uint32_t i = 0; i < TIMESIZE; ++i) {
    std::cout << " " << std::setw(3) << i;
  }
  std::cout << "\n";
  for (auto i: diary_) {
    std::cout << counter++ << ":\t";
    for (auto c: i) {
      switch(c) {
      case State::Awake:
        std::cout << " .  ";
        break;
      case State::Sleep: 
        std::cout << " #  ";
        break;
      }
    }
    std::cout << "\n";
  }
}
