#pragma once

#include "g3/basis.h"
#include <array>

namespace g3 {
struct MultivectorLayout {
  static constexpr char name[] = "MultivectorLayout";
  static constexpr uint8_t dimension = 8;
  static constexpr basis::Element idx_to_basis[]{
      basis::Element::E0,  basis::Element::E1,  basis::Element::E2,
      basis::Element::E3,  basis::Element::E12, basis::Element::E23,
      basis::Element::E13, basis::Element::E123};

  static constexpr uint8_t basis_to_idx(const basis::Element e) {
    return static_cast<int8_t>(e) - 1;
  }
};
} // namespace g3
