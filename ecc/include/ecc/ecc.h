#pragma once

#include "ecc/key.h"

#include <vector>
#include <memory>

namespace Ecc
{

class ISignature
{
public:
    virtual unsigned char* data() const = 0;
    virtual uint16_t getLength() const = 0;
    virtual void setLength(const uint16_t &value) = 0;
};


/** Holds data belonging to a signature
  Call setLength with the desired length of the signature, before using the data pointer.
  Otherwise you will receive nullptr.
*/
class Signature : public ISignature {
public:
    /** Gets pointer to data of signature */
    unsigned char* data() const;
    /** Gets length of signature */
    uint16_t getLength() const;
    /** Sets length of signature and changes data size accordingly */
    void setLength(const uint16_t &value);
private:
    std::shared_ptr<std::vector<unsigned char>> getDataVector() const;
    void setDataVector(const std::shared_ptr<std::vector<unsigned char>> &value);
    std::shared_ptr<std::vector<unsigned char>> data_{nullptr};
    uint16_t length_{0};
};

std::unique_ptr<ISignature> sign(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash);
bool verify(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash, std::unique_ptr<ISignature> const & signature);

}
