#pragma once

#include "g3/basis.h"
#include "g3/scalar.h"
#include "g3/unroll_macro.h"

#include <array>
#include <iostream>

namespace g3 {

template <typename TLayoutA, typename TLayoutB, typename TLayoutC>
void unrolled_multiply(const Scalar *a, const Scalar *b, Scalar *c) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
  // for (auto basis : TlayoutC::idx_to_basis)
  G3_UNROLL(basis, TLayoutC::idx_to_basis, TLayoutC::dimension,
            // loop body
            c[basis_idx] = 0;) // End macro

  // for (auto ae : TLayoutA::idx_to_basis)
  G3_UNROLL(ae, TLayoutA::idx_to_basis, TLayoutA::dimension,
            // for (auto be : TLayoutB::idx_to_basis)
            G3_UNROLL(be, TLayoutB::idx_to_basis, TLayoutB::dimension,
                      // loop body
                      constexpr basis::SignedElement abe = ae * be;
                      const Scalar ab_prod = a[ae_idx] * b[be_idx] * abe.sign;
                      c[TLayoutC::basis_to_idx(abe.element)] +=
                      ab_prod;)) // End macro

#pragma GCC diagnostic pop
}

// For benchmarking comparison and reference implementation
template <typename TLayoutA, typename TLayoutB, typename TLayoutC>
void rolled_multiply(const Scalar *a, const Scalar *b, Scalar *c) {
  for (int i = 0; i < TLayoutC::dimension; ++i) {
    c[i] = 0;
  }
  for (int ae_idx = 0; ae_idx < TLayoutA::dimension; ++ae_idx) {
    const basis::Element ae = TLayoutA::idx_to_basis[ae_idx];
    for (int be_idx = 0; be_idx < TLayoutB::dimension; ++be_idx) {
      const basis::Element be = TLayoutB::idx_to_basis[be_idx];
      const basis::SignedElement abe = ae * be;
      const Scalar ab_prod = a[ae_idx] * b[be_idx] * abe.sign;
      c[TLayoutC::basis_to_idx(abe.element)] += ab_prod;
    }
  }
}

} // namespace g3
