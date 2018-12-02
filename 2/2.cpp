#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

bool at_most_one_char_diff(const std::string &s1, const std::string &s2) {
  if (s1.size() != s2.size())
    return false;
  bool char_differ = false;
  for (size_t i = 0; i < s1.size(); ++i) {
    if (s1[i] != s2[i]) {
      if (char_differ == true)
        return false;
      char_differ = true;
    }
  }
  return true;
}

std::string get_common_part(const std::string &s1, const std::string &s2) {
  std::string result;
  for (size_t i = 0; i < s1.size(); ++i) {
    if (s1[i] == s2[i]) {
      result += s1[i];
    }
  }
  return result;
}

int main(int argc, char **argv) {
  std::ifstream input(argv[1]);
  std::vector<std::string> lines;
  std::copy(std::istream_iterator<std::string>(input),
            std::istream_iterator<std::string>(), std::back_inserter(lines));

  for (size_t i = 0; i < lines.size() - 1; ++i) {
    for (size_t j = i + 1; j < lines.size(); ++j) {
      if (at_most_one_char_diff(lines[i], lines[j])) {
        std::cout << get_common_part(lines[i], lines[j]) << "\n";
        return 0;
      }
    }
  }
  std::cout << "Didn't found matching string :( \n";
  return 0;
}
