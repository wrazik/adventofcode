#pragma once
enum class BoxState {
  Free,
  Busy,
  Overlapping,
};

struct Claim {
  size_t id;
  size_t rows;
  size_t cols;
  size_t x;
  size_t y;
};
