#pragma once

#include "ecc/key.h"

#include <vector>
#include <memory>

namespace Ecc
{

class ISignature
{
public:
    //todo delete default constructor?
   // explicit ISignature(int16_t length);
    //ISignature() = delete;
    virtual std::shared_ptr<std::vector<unsigned char>> getData() const = 0;
    virtual void setData(const std::shared_ptr<std::vector<unsigned char>> &value) = 0;
    virtual uint16_t getLength() const = 0;
    virtual void setLength(const uint16_t &value) = 0;

};

class Signature : public ISignature {
public:
    //explicit Signature(int16_t length);
   // Signature() = delete;
    std::shared_ptr<std::vector<unsigned char>> getData() const;
    void setData(const std::shared_ptr<std::vector<unsigned char>> &value);
    uint16_t getLength() const;
    void setLength(const uint16_t &value);
private:
    std::shared_ptr<std::vector<unsigned char>> data{nullptr};
    uint16_t length{0};

};

std::unique_ptr<ISignature> sign(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash);
bool verify(std::unique_ptr<IKey> const & key, std::vector<uint8_t> const & hash, std::unique_ptr<ISignature> const & signature);

}
