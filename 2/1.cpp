#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

bool exists_char_exactly_n(const std::string &input, size_t n) {
  std::unordered_map<char, size_t> char_counter;
  for (auto c : input) {
    ++char_counter[c];
  }
  return std::find_if(char_counter.begin(), char_counter.end(),
                      [n](const auto &pair) { return pair.second == n; }) !=
         char_counter.end();
}

int main(int argc, char **argv) {
  std::ifstream input(argv[1]);
  std::vector<std::string> lines;
  std::copy(std::istream_iterator<std::string>(input),
            std::istream_iterator<std::string>(), std::back_inserter(lines));

  const size_t exactly_two =
      std::count_if(lines.begin(), lines.end(), [](const auto &line) {
        return exists_char_exactly_n(line, 2);
      });

  const size_t exactly_three =
      std::count_if(lines.begin(), lines.end(), [](const auto &line) {
        return exists_char_exactly_n(line, 3);
      });

  std::cout << exactly_two*exactly_three << "\n";
}
