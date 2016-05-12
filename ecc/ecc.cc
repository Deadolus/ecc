#include "ecc/ecc.h"

#include <crypto/cryptoApi.h>

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

  // ...

  return nullptr;
}

/// verify that the signature of a hash has been signed (with the correct private key) by the public key
/// @param key public key to use for verifying
/// @param hash Hash which was signed
/// @param signature Received signature of signed hash
bool verify(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash, std::unique_ptr<ISignature> const & signature) {
  initialize();

  // ...

  return false;
}

}

