#pragma once

#include "g3/multivector_base.h"
#include "g3/multivector_layout.h"

namespace g3 {
class Multivector : public MultivectorBase<Multivector, MultivectorLayout> {
 public:
  template <typename TOther>
  TOther get() const {
    TOther result;
    for (size_t i = 0; i < TOther::layout_type::dimension; ++i) {
      result.data()[i] = (*this)[TOther::layout_type::idx_to_basis[i]];
    }
    return result;
  }

  template <typename TOther>
  static Multivector From(const TOther& other) {
    return Multivector::Zero() + other;
  }
};

} // namespace g3
