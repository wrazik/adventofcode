#include <fabric.hpp>

#include <algorithm>
#include <numeric>
#include <fstream>

Fabric::Fabric() {
  for(auto& row: fields_) {
    row.fill(BoxState::Free);
  }
}

char Fabric::ToChar(const BoxState &s) {
  switch (s) {
  case BoxState::Free:
    return '.';
  case BoxState::Busy:
    return 'X';
  case BoxState::Overlapping:
    return 'O';
  }
  return '\0';
}

std::string Fabric::RowToString(const std::array<BoxState, SIZE> &row) {
  std::string output;
  output.reserve(SIZE);
  std::transform(row.begin(), row.end(), std::back_inserter(output),
                 Fabric::ToChar);
  return output;
}

size_t Fabric::Count(const BoxState &s) const {
  return std::accumulate(fields_.begin(), fields_.end(), 0u,
                         [s](size_t prev, const auto &row) {
                           return prev + std::count(row.begin(), row.end(), s);
                         });
}

void Fabric::AddClaim(const Claim& c) {
  for (size_t i = c.x; i < c.x + c.cols; ++i) {
    for (size_t j = c.y; j < c.y + c.rows; ++j) {
      auto& field = Get(i, j);
      switch(field) {
        case BoxState::Free:
          field = BoxState::Busy;
          break;
        case BoxState::Busy:
          field = BoxState::Overlapping;
          break;
        default: ;//empty;
      }
    }
  }
}

void Fabric::SaveToFile(const std::string &filename) {
  std::ofstream file(filename);
  for (const auto &row : fields_) {
    file << RowToString(row) << "\n";
  }
}

BoxState &Fabric::Get(size_t x, size_t y) { return fields_[y][x]; }
