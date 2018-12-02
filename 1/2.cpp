#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>

int main(int argc, char **argv) {
  std::ifstream input(argv[1]);
  std::vector<int64_t> nums;
  std::transform(
      std::istream_iterator<std::string>(input),
      std::istream_iterator<std::string>(), std::back_inserter(nums),
      [](const auto &line) { return static_cast<int64_t>(std::stol(line)); });
  std::unordered_set<int64_t> freqs{0};
  int64_t current_freq{0};
  bool was_inserted = true;
  while(was_inserted) {
    for(auto i: nums) {
      current_freq += i;
      was_inserted = freqs.emplace(current_freq).second;
      if (!was_inserted) {
        break;
      }
    }
  }
  std::cout << current_freq << "\n";
  return 0;
}

