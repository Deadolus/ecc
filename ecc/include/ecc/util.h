#pragma once

#include <vector>
#include <string>

namespace Ecc {

std::vector<uint8_t> to_hex(std::string const & string);
std::string to_string(std::vector<uint8_t> const & hex);

}
