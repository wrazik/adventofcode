#pragma once
#include <array>
#include <string>

#include <types.hpp>

class Fabric {
public:
  static constexpr size_t SIZE = 1020;
  std::array<std::array<BoxState, SIZE>, SIZE> fields_;
	Fabric();

  static char ToChar(const BoxState &s);
  static std::string RowToString(const std::array<BoxState, SIZE> &row);
  void SaveToFile(const std::string &filename);
	void AddClaim(const Claim& c);
  size_t Count(const BoxState &s) const;
	BoxState& Get(size_t x, size_t y); 
};
