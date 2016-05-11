#include "ecc/util.h"

#include <sstream>
#include <iterator>
#include <iomanip>
#include <algorithm>

namespace Ecc {

std::vector<uint8_t> to_hex(std::string const & string) {
  std::vector<uint8_t> hex{};
  for(size_t i = 0; i < string.length(); i += 2) {
    hex.push_back(std::stoul(string.substr(i, 2), nullptr, 16));
  }
  return hex;
}

std::string to_string(std::vector<uint8_t> const & hex) {
  std::ostringstream string;
  string << std::hex << std::uppercase << std::setfill('0');
  for(uint32_t const value : hex) {
    string << std::setw(2) << value;
  }
  return string.str();
}

}

