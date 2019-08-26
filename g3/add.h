#pragma once

#include "g3/basis.h"
#include "g3/scalar.h"

namespace g3 {

// Add a into b
template <typename TLayoutA, typename TLayoutC>
void add_into(const Scalar *a, Scalar *c) {
  // Manually add idx 0 because of the QuaternionLayout case
  // which does not have a contiguous basis

  c[TLayoutC::basis_to_idx(TLayoutA::idx_to_basis[0])] += a[0];
  const uint8_t start_idx_a_to_c =
      TLayoutC::basis_to_idx(TLayoutA::idx_to_basis[1]);
  for (int i = 1; i < TLayoutA::dimension; ++i) {
    c[start_idx_a_to_c + i - 1] += a[i];
  }
}

// For benchmarking comparison and reference implementation
// Testing shows that the rolled version is faster
template <typename TLayoutA, typename TLayoutB, typename TLayoutC>
void add(const Scalar *a, const Scalar *b, Scalar *c) {
  for (int i = 0; i < TLayoutC::dimension; ++i) {
    c[i] = 0;
  }
  add_into<TLayoutA, TLayoutC>(a, c);
  add_into<TLayoutB, TLayoutC>(b, c);
}

} // namespace g3
