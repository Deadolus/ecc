#include "ecc/key.h"
#include "ecc/util.h"

#include <crypto/cryptoApi.h>

namespace Ecc
{

std::unique_ptr<IKey> public_key(std::string key) {

  // ...

  return nullptr;
}

std::unique_ptr<IKey> private_key(std::string key) {
  auto private_key = to_hex(key);
  psEccKey_t matrixssl_key;
  int32_t const result = psEccParsePrivKey(nullptr, private_key.data(), private_key.size(), &matrixssl_key, nullptr);
  if(result != PS_SUCCESS) {
    throw;
  }

  // ...

  return nullptr;
}

}
