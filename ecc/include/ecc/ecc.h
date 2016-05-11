#pragma once

#include "ecc/key.h"

#include <vector>
#include <memory>

namespace Ecc
{

class ISignature
{
};

std::unique_ptr<ISignature> sign(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash);
bool verify(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash, std::unique_ptr<ISignature> const & signature);

}
