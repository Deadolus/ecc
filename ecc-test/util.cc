#include <gmock/gmock.h>

#include <ecc/ecc.h>
#include <ecc/util.h>

namespace {

using namespace testing;
using namespace std::literals::string_literals;

TEST(to_hex, converts_string_into_a_hex_vector) {
  std::vector<uint8_t> const expected{0x01, 0x23};
  ASSERT_THAT(Ecc::to_hex("0123"s), ContainerEq(expected));
}

TEST(to_hex, can_handle_values_bigger_than_hex_7F) {
  std::vector<uint8_t> const expected{0x80, 0x90, 0xFF};
  ASSERT_THAT(Ecc::to_hex("8090FF"s), ContainerEq(expected));
}

TEST(to_string, converts_a_hex_vector_to_string) {
  ASSERT_THAT(Ecc::to_string({0x70, 0x61, 0x52, 0x43}), StrEq("70615243"s));
}

TEST(to_string, uses_uppercase_letters) {
  ASSERT_THAT(Ecc::to_string({0xAB, 0xCD, 0xEF}), StrEq("ABCDEF"s));
}

TEST(to_string, pads_values_smaller_then_hex_10_with_a_zero) {
  ASSERT_THAT(Ecc::to_string({0x0, 0x1, 0x9, 0xA, 0xF}), StrEq("0001090A0F"s));
}

}

