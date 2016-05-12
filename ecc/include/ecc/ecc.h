#pragma once

#include "ecc/key.h"

#include <vector>
#include <memory>

namespace Ecc
{

class ISignature
{
    virtual std::shared_ptr<unsigned char> getData() const = 0;
    virtual void setData(const std::shared_ptr<unsigned char> &value) = 0;
    virtual uint16_t getLength() const = 0;
    virtual void setLength(const uint16_t &value) = 0;

};

class Signature : public ISignature {
    std::shared_ptr<unsigned char> data = nullptr;
    uint16_t length = 0;

public:
    std::shared_ptr<unsigned char> getData() const;
    void setData(const std::shared_ptr<unsigned char> &value);
    uint16_t getLength() const;
    void setLength(const uint16_t &value);
};

std::unique_ptr<ISignature> sign(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash);
bool verify(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash, std::unique_ptr<ISignature> const & signature);

}
