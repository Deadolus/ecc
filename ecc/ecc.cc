#include "ecc/ecc.h"
#include <crypto/cryptoApi.h>

#include <memory>
#include <vector>

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
    psPool_t *pool = NULL;;
    std::unique_ptr<Signature> signature(new Signature);
    signature->setLength(128);
    psEccKey_t private_key = key->getKey();
    uint16_t sig_length = signature->getLength();
    uint16_t hash_length = hash.size()*sizeof(hash.data());

    if (psEccDsaSign(pool, &private_key, hash.data(), hash_length, signature->data(), &sig_length, 0, NULL) < 0) {
        //_psTrace("Signing failed.\n");
        return nullptr;
    }
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
    uint16_t sig_length = signature->getLength();
    uint16_t hash_length = hash.size()*sizeof(hash.data());

    if (psEccDsaVerify(pool, &public_key, hash.data(), hash_length, signature->data(),  sig_length,
                       &status, NULL) < 0 || status != 1) {
        //_psTrace("Signature didn't validate.");
        return false;
    }
    return true;
}

std::shared_ptr<std::vector<unsigned char>> Signature::getDataVector() const
{
    return data_;
}

unsigned char* Signature::data() const
{
    return data_->data();
}

void Signature::setDataVector(const std::shared_ptr<std::vector<unsigned char>> &value)
{
    data_ = value;
}

uint16_t Signature::getLength() const
{
    return length_;
}

void Signature::setLength(const uint16_t &value)
{
    length_ = value;
    if(!data_)
        data_ = std::make_shared<std::vector<unsigned char>>();
    data_->resize(length_);
}
}

