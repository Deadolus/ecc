#include "ecc/ecc.h"
#include <memory>
#include <vector>

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
  psPool_t			*pool = nullptr;
  const psEccCurve_t	*curve;

  //unsigned char signature[128]{};
    std::unique_ptr<Signature> signature(new Signature);
  //Initialize stuff
  if (getEccParamById(IANA_SECP256R1, &curve) < 0) {
    return nullptr;
  }
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
uint16_t length = signature->getLength();
  if (psEccDsaSign(pool, &private_key, hash.data(), hash.size(), signature->getData().get(), &length, 0, NULL) < 0) {
      _psTrace("Signing failed.");
      return nullptr;
  }
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

  // ...
  //psEccDsaVerify();
          /*if (psEccDsaVerify(pool, &k1_imported, in, inlen, signature->data, signature->length,
                  &status, NULL) < 0 || status != 1) {
              _psTrace("K1 signature didn't validate.");
              return false;
          }*/

  return false;
}

std::shared_ptr<unsigned char> Signature::getData() const
{
    return data;
}

void Signature::setData(const std::shared_ptr<unsigned char> &value)
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
}
}

