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

std::unique_ptr<ISignature> sign(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash) {
  initialize();

  // ...

  return nullptr;
}

bool verify(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash, std::unique_ptr<ISignature> const & signature) {
  initialize();

  // ...

  return false;
}

}

