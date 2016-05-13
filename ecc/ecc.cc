#include "ecc/ecc.h"
#include <memory>
#include <vector>

#include <iostream>

#include <crypto/cryptoApi.h>
#define USE_SECP256R1

namespace {

static bool initialized = false;

inline void initialize() {
  if(not initialized) {
    psCryptoOpen(PSCRYPTO_CONFIG);
    initialized = true;
  }
}

}

namespace Ecc {

  /// Sign some data with a private key
  /// @param key Key with which to sign the hash
  /// @param hash Hash (data) to be signed
  /// @return Signature of the signed hash
std::unique_ptr<ISignature> sign(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash) {
  initialize();
  psPool_t			*pool = NULL;
  //const psEccCurve_t	*curve;

  //unsigned char signature[128]{};
    std::unique_ptr<Signature> signature(new Signature);
  //std::unique_ptr<Signature> signature(128);
    signature->setLength(128);
    //unsigned char		sk1k2[128];
    //std::cout << "size of sk1k2 "<<sizeof(sk1k2);
  //Initialize stuff
  /*if (getEccParamById(IANA_SECP256R1, &curve) < 0) {
    return nullptr;
  }
  _psTrace("After getEccParamById");*/
  /*if (psEccGenKey(pool, &k1, curve, NULL) < 0) {
      return nullptr;
  }*/
  /*if (psEccX963ImportKey(pool, key, key->length, &privateKey, curve) < 0) {
      return nullptr;
  }*/
  /*
  secretlen = sizeof(signature);
  if (psEccGenSharedSecret(pool, &k2, &k1_imported, sk2k1, &secretlen, NULL) < 0 ||
          secretlen != curve->size) {
      _psTrace("GenSharedSecret K2 failed.");
      goto L_FAIL;
  }*/
psEccKey_t private_key = key->getKey();
  _psTrace("After getKey\n");
//uint16_t sig_length = sizeof(signature->getData());
  uint16_t sig_length = signature->getLength();
  uint16_t hash_length = hash.size()*sizeof(hash.data());
  std::cout << "Sig length"<<sig_length<<" Hash length"<<hash_length<<"\n";
  if (psEccDsaSign(pool, &private_key, hash.data(), hash_length, signature->getData()->data(), &sig_length, 0, NULL) < 0) {
      _psTrace("Signing failed.\n");
      return nullptr;
  }
    _psTrace("After signing\n");
 //psEccNewKey(pool, key, eccCurve);
  //Process signature with hash
  //signature = psEccDsaSign(pool, eccKey, hash, hash.size(),  ) ;
  //psEccClearKey(&privateKey);

  // ...

  //psCryptoClose();
  return signature;
}

/// verify that the signature of a hash has been signed (with the correct private key) by the public key
/// @param key public key to use for verifying
/// @param hash Hash which was signed
/// @param signature Received signature of signed hash
bool verify(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash, std::unique_ptr<ISignature> const & signature) {
  initialize();
    psPool_t *pool = nullptr;
    int32_t status;
    psEccKey_t public_key = key->getKey();

  // ...
  //psEccDsaVerify();
    uint16_t sig_length = signature->getLength();
    uint16_t hash_length = hash.size()*sizeof(hash.data());
          if (psEccDsaVerify(pool, &public_key, hash.data(), hash_length, signature->getData()->data(),  sig_length,
                  &status, NULL) < 0 || status != 1) {
              _psTrace("K1 signature didn't validate.");
              return false;
          }
            //if (psEccDsaSign(pool, &private_key, hash.data(), hash_length, signature->getData()->data(), &sig_length, 0, NULL) < 0)

  return true;
}

/*Signature::Signature(int16_t length):length(length) {
    data = std::make_shared<std::vector<unsigned char>>();
    data->resize(length);
}*/

std::shared_ptr<std::vector<unsigned char>> Signature::getData() const
{
    return data;
}

void Signature::setData(const std::shared_ptr<std::vector<unsigned char>> &value)
{
    data = value;
}

uint16_t Signature::getLength() const
{
    return length;
}

void Signature::setLength(const uint16_t &value)
{
    length = value;
    if(!data)
        data = std::make_shared<std::vector<unsigned char>>();
    data->resize(length);
}
}

