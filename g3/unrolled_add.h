#pragma once

#include "g3/add.h"
#include "g3/basis.h"
#include "g3/scalar.h"
#include "g3/unroll_macro.h"

namespace g3 {

template <typename TLayoutA, typename TLayoutB, typename TLayoutC>
void unrolled_add(const Scalar *a, const Scalar *b, Scalar *c) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
  // for (auto basis : TlayoutC::idx_to_basis)
  G3_UNROLL(basis, TLayoutC::idx_to_basis, TLayoutC::dimension,
            // loop body
            c[basis_idx] = 0;)

  // for (auto basis : TLayoutA::idx_to_basis)
  G3_UNROLL(basis, TLayoutA::idx_to_basis, TLayoutA::dimension,
            // loop body
            c[TLayoutC::basis_to_idx(basis)] += a[basis_idx];) // End macro

  // for (auto basis : TLayoutB::idx_to_basis)
  G3_UNROLL(basis, TLayoutB::idx_to_basis, TLayoutB::dimension,
            // loop body
            c[TLayoutC::basis_to_idx(basis)] += b[basis_idx];) // End macro

#pragma GCC diagnostic pop
}

// For benchmarking comparison and reference implementation
// Testing shows that the rolled version is faster
template <typename TLayoutA, typename TLayoutB, typename TLayoutC>
void rolled_add(const Scalar *a, const Scalar *b, Scalar *c) {
  add<TLayoutA, TLayoutB, TLayoutC>(a, b, c);
}

} // namespace g3
