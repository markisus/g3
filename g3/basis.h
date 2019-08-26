#pragma once

#include <cstdint>
#include <iostream>

#include "g3/scalar.h"

namespace g3 {
namespace basis {

enum class Element : int8_t {
  E0 = 1,
  E1 = 2,
  E2 = 3,
  E3 = 4,
  E12 = 5,
  E23 = 6,
  E13 = 7,
  E123 = 8,
  INVALID = 0
};

inline std::ostream &operator<<(std::ostream &os, const Element element) {
  switch (element) {
  case Element::E0:
    os << "E0";
    break;
  case Element::E1:
    os << "E1";
    break;
  case Element::E2:
    os << "E2";
    break;
  case Element::E3:
    os << "E3";
    break;
  case Element::E12:
    os << "E12";
    break;
  case Element::E23:
    os << "E23";
    break;
  case Element::E13:
    os << "E13";
    break;
  case Element::E123:
    os << "E123";
    break;
  default:
    os << "???";
    break;
  }
  return os;
}

struct SignedElement {
  constexpr SignedElement(Element e, int8_t s) : element(e), sign(s){};

  static constexpr SignedElement Positive(Element e) {
    return SignedElement(e, 1);
  };
  static constexpr SignedElement Negative(Element e) {
    return SignedElement(e, -1);
  }

  constexpr bool is_positive() const { return !is_negative(); }

  constexpr bool is_negative() const { return sign < 0; }

  Element element;
  int8_t sign;
};

constexpr uint8_t E0 = static_cast<uint8_t>(Element::E0);
constexpr uint8_t E1 = static_cast<uint8_t>(Element::E1);
constexpr uint8_t E2 = static_cast<uint8_t>(Element::E2);
constexpr uint8_t E3 = static_cast<uint8_t>(Element::E3);
constexpr uint8_t E12 = static_cast<uint8_t>(Element::E12);
constexpr uint8_t E23 = static_cast<uint8_t>(Element::E23);
constexpr uint8_t E13 = static_cast<uint8_t>(Element::E13);
constexpr uint8_t E123 = static_cast<uint8_t>(Element::E123);

// clang-format off
constexpr int8_t BASIS_PRODUCT[8][8] = {
  {E0,    E1,    E2,   E3,    E12,   E23,   E13,   E123,},
  {E1,    E0,    E12,  E13,   E2,    E123,  E3,    E23, },
  {E2,   -E12,   E0,   E23,  -E1,    E3,   -E123, -E13, },
  {E3,   -E13,  -E23,  E0,    E123, -E2,   -E1,    E12, },
  {E12,  -E2,    E1,   E123, -E0,    E13,  -E23,  -E3,  },
  {E23,   E123, -E3,   E2,   -E13,  -E0,    E12,  -E1,  },
  {E13,  -E3,   -E123, E1,    E23,  -E12,  -E0,    E2,  },
  {E123,  E23,  -E13,  E12,  -E3,   -E1,    E2,   -E0   },
};
// clang-format on

constexpr SignedElement operator*(Element b1, Element b2) {
  if (b1 == Element::INVALID || b2 == Element::INVALID) {
    return SignedElement::Positive(Element::INVALID);
  }
  const int8_t product =
      BASIS_PRODUCT[static_cast<int8_t>(b1) - 1][static_cast<int8_t>(b2) - 1];
  return product > 0 ? SignedElement::Positive(Element(product))
                     : SignedElement::Negative(Element(-product));
}

constexpr SignedElement operator*(const SignedElement b1,
                                  const SignedElement b2) {
  SignedElement result = b1.element * b2.element;
  result.sign *= b1.sign * b2.sign;
  return result;
}

constexpr SignedElement operator*(const SignedElement b1, const Element b2) {
  SignedElement result = b1.element * b2;
  result.sign *= b1.sign;
  return result;
}

constexpr SignedElement operator*(const Element b1, const SignedElement b2) {
  SignedElement result = b1 * b2.element;
  result.sign *= b2.sign;
  return result;
}

inline std::ostream &operator<<(std::ostream &os,
                                const SignedElement signed_element) {
  if (signed_element.sign < 0) {
    os << "-";
  }
  os << signed_element.element;
  return os;
}

} // namespace basis
} // namespace g3
