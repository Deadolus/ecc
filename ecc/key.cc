#include "ecc/key.h"
#include "ecc/util.h"

#include <crypto/cryptoApi.h>

namespace Ecc
{

std::unique_ptr<IKey> public_key(std::string key) {
    /*;
    psEccKey_t matrixssl_key;
    int32_t const result = psEccParsePublicKey(nullptr, public_key.data(), public_key.size(), &matrixssl_key, nullptr);
    if(result != PS_SUCCESS) {
      throw;
    }*/
    auto public_key = to_hex(key);
      psPool_t *pool = nullptr;
    int32_t rc;
    psEccKey_t matrixssl_key;
    const psEccCurve_t	*curve;
    rc = psEccX963ImportKey(pool, public_key.data(), public_key.size() ,
                            &matrixssl_key, curve);
    if (rc != PS_SUCCESS) {
        _psTrace("psEccX963ImportKey failed\n");
        rc = PS_FAIL;
        return nullptr;
    }

    std::unique_ptr<Key> retkey(new Key);
    if(!retkey) {
        _psTrace("Couldn't create key\n");
      return nullptr;
    }
    retkey->setKey(matrixssl_key);
    return retkey;
}

std::unique_ptr<IKey> private_key(std::string key) {
  auto private_key = to_hex(key);
  psEccKey_t matrixssl_key;
  int32_t const result = psEccParsePrivKey(nullptr, private_key.data(), private_key.size(), &matrixssl_key, nullptr);
  if(result != PS_SUCCESS) {
    throw;
  }

  std::unique_ptr<Key> retkey(new Key);
  if(!retkey) {
      _psTrace("Couldn't create key\n");
    return nullptr;
  }
  retkey->setKey(matrixssl_key);
  return retkey;
}

psEccKey_t Key::getKey() const
{
    return key;
}

void Key::setKey(const psEccKey_t &value)
{
    key = value;
}

}
