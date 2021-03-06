#pragma once

#include "g3/basis.h"
#include <array>

namespace g3 {
struct QuaternionLayout {
  static constexpr char name[] = "QuaternionLayout";
  static constexpr uint8_t dimension = 4;
  static constexpr basis::Element idx_to_basis[]{
      basis::Element::E0, basis::Element::E12, basis::Element::E23,
      basis::Element::E13,

      // dummy values to prevent compiler error during loop unrolling
      basis::Element::INVALID, basis::Element::INVALID, basis::Element::INVALID,
      basis::Element::INVALID};

  static constexpr uint8_t basis_to_idx(const basis::Element e) {
    switch (e) {
    case basis::Element::E0:
      return 0;
    case basis::Element::E12:
      return 1;
    case basis::Element::E23:
      return 2;
    case basis::Element::E13:
      return 3;
    default:
      return static_cast<uint8_t>(-1);
    }
  }
};
} // namespace g3
