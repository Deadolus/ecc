#include <gmock/gmock.h>

#include <ecc/ecc.h>
#include <ecc/util.h>

#include <iostream>

namespace {

using namespace testing;

TEST(elliptic_curve, signature) {

  using namespace std::literals::string_literals;

  // arrange
  auto sign_key = Ecc::private_key("30770201010420c46bb852f9e00599f38cb4aa8fdd6bf2a7977489a378724bfd547b5829ebfec9a00a06082a8648ce3d030107a144034200044c80dd9f5a55bc0a5f238af358d1d285109cce71152e459b380bc3bc62fb715685f9e51702a412cf31917f93a5d0d9f37e634ffc79246614cb2edd7cfb3c8bd1"s);
  auto verify_key = Ecc::public_key("044C80DD9F5A55BC0A5F238AF358D1D285109CCE71152E459B380BC3BC62FB715685F9E51702A412CF31917F93A5D0D9F37E634FFC79246614CB2EDD7CFB3C8BD1"s);
  auto hash = Ecc::to_hex("2e5cac9057a25dc1da89e0ee243f74e8a84153143e6935fb0a71271365e0ae7f");
  // act
  auto signature = Ecc::sign(sign_key, hash);
  if(signature)
    std::cout << "Signature: "<< signature->getData();

  // assert
  //ASSERT_TRUE(true);
  ASSERT_TRUE(Ecc::verify(verify_key, hash, signature));
}



}

