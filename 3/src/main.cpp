#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

#include <fabric.hpp>
#include <parser.hpp>
#include <types.hpp>

int main(int argc, char** argv) {
  if (argc != 2)
    return 1;
  std::ifstream file(argv[1]);
  std::vector<std::string> lines;

  for (std::string line; std::getline(file, line);) {
    lines.push_back(std::move(line));
  }

  Fabric f;
	std::vector<Claim> claims;
  for (const auto &line : lines) {
    Claim c = Parser::ParseClaim(line);
		claims.push_back(std::move(c));
    f.AddClaim(claims.back());
  }
  std::cout << "overlapping count: " << f.Count(BoxState::Overlapping) << "\n";
  for(const auto claim: claims) {
    if (f.IsNotShared(claim)) {
      std::cout << "id: #" << claim.id << " is not shared with any other claim!\n";
    }
  }
}
