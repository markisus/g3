#pragma once

#include "g3/basis.h"
#include "g3/scalar.h"
#include "g3/unrolled_multiply.h"

namespace g3 {

template <typename TLayoutA, typename TLayoutB, typename TLayoutC>
void multiply(const Scalar *a, const Scalar *b, Scalar *c) {
  unrolled_multiply<TLayoutA, TLayoutB, TLayoutC>(a, b, c);
}

} // namespace g3
