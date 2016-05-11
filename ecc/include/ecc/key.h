#pragma once

#include <memory>
#include <string>

namespace Ecc
{

class IKey
{
};

std::unique_ptr<IKey> public_key(std::string key);
std::unique_ptr<IKey> private_key(std::string key);

}
