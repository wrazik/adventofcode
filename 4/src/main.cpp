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
  const auto [prop, hour] = guard.GetMostPropableHour();
  std::cout << "id: " << id << " hour: " << hour << ", answer: " << hour*id << "\n";
}
