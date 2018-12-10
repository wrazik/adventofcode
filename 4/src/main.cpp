#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

#include <parser.hpp>

int main(int argc, char** argv) {
  if (argc != 2)
    return 1;
  std::ifstream file(argv[1]);
  std::vector<std::string> lines;

  for (std::string line; std::getline(file, line);) {
    lines.push_back(std::move(line));
  }

	std::sort(lines.begin(), lines.end());

	Parser p;
	for (const auto& line: lines) {
		p.AddLine(line);
	}
  const auto [id, guard] = p.GetMostSleeping();
  const auto [count, hour] = guard.GetMostFrequentHour();
  std::cout << "Strategy1: id: " << id << " hour: " << hour << ", answer: " << hour*id << "\n";


  const auto [s2_id, s2_hour] = p.GetMostFrequentHour();
  std::cout << "Strategy2: id: " << s2_id << " hour: " << s2_hour << ", answer: " << s2_hour*s2_id << "\n";
}
