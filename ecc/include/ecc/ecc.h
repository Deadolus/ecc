#pragma once

#include <array>

namespace Ecc
{

class IKey
{
};

template<size_t HashSize>
sign(IKey const & key, std::array<uint8_t, HashSize> const & hash);

}
