#pragma once

#include "g3/basis.h"

namespace g3 {
struct ScalarLayout {
  static constexpr uint8_t dimension = 1;
  static constexpr int8_t idx_to_basis[dimension] = {basis::E0};
  static constexpr uint8_t basis_to_idx(const int8_t e) {
    return e == basis::E0 ? 0 : -1;
  }
};
} // namespace g3
