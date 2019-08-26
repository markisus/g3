#pragma once

#include "g3/multivector_layout.h"
#include "g3/quaternion_layout.h"
#include "g3/vector_layout.h"
#include <type_traits>

namespace g3 {

template <typename TFrom, typename TTo>
struct ValidUpCast : std::integral_constant<bool, false> {};

#define VALID_UP_CAST(FROM, TO)                                                \
  template <>                                                                  \
  struct ValidUpCast<FROM, TO> : std::integral_constant<bool, true> {};

VALID_UP_CAST(VectorLayout, QuaternionLayout)
VALID_UP_CAST(VectorLayout, MultivectorLayout)
VALID_UP_CAST(QuaternionLayout, MultivectorLayout)

} // namespace g3
