#include "ecc/key.h"
#include "ecc/util.h"
extern "C" {
#include <crypto/cryptoApi.h>
}

#include <iostream>

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
      psPool_t *pool = NULL;

    psEccKey_t matrixssl_key = { 0};// PS_ECC_STATIC_INIT;
        int32_t rc = PS_FAIL;

    const psEccCurve_t	*curve;
    int curve_id = 0;
    if (getEccParamById(IANA_SECP256R1, &curve) < 0) {
      return nullptr;
    }
       // _psTrace("before importkey\n");
        //std::cout << "Public key size"<<public_key.size()<<"\n";
        //std::cout << "Public key data"<<public_key.data()<<"\n";
    rc = psEccX963ImportKey(pool, public_key.data(), public_key.size() ,
                            &matrixssl_key, curve);
   // _psTrace("After importkey\n");
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
       // _psTrace("After setkey\n");
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
