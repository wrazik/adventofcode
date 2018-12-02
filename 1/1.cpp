#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  std::ifstream input(argv[1]);
  std::vector<int64_t> nums;
  std::transform(
      std::istream_iterator<std::string>(input),
      std::istream_iterator<std::string>(), std::back_inserter(nums),
      [](const auto &line) { return static_cast<int64_t>(std::stol(line)); });
  std::cout << std::accumulate(nums.begin(), nums.end(), 0l) << "\n";
  return 0;
}
