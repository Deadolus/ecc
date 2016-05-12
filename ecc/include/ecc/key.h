#pragma once

#include "crypto/cryptoApi.h"

#include <memory>
#include <string>

namespace Ecc
{

class IKey
{
public:
    virtual psEccKey_t getKey() const = 0;
    virtual void setKey(const psEccKey_t &value) = 0;
};

class Key : public IKey
{

    psEccKey_t key;
    //int32_t* key = nullptr;
    //size_t length = 0;

public:
    psEccKey_t getKey() const;
    void setKey(const psEccKey_t &value);
};

std::unique_ptr<IKey> public_key(std::string key);
std::unique_ptr<IKey> private_key(std::string key);

}
