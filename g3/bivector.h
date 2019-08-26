#pragma once

#include "g3/multivector_base.h"
#include "g3/bivector_layout.h"

namespace g3 {

class Bivector : public MultivectorBase<Bivector, BivectorLayout> {
public:
  // Needed because functions do not overload across scopes
  using MultivectorBase<Bivector, BivectorLayout>::operator+;
  using MultivectorBase<Bivector, BivectorLayout>::operator*;
  using MultivectorBase<Bivector, BivectorLayout>::operator*=;
  using MultivectorBase<Bivector, BivectorLayout>::operator/;
  using MultivectorBase<Bivector, BivectorLayout>::operator/=;

  Scalar i() const;
  Scalar j() const;
  Scalar k() const;

  Bivector inverted() const;
  Bivector &invert();
};
} // namespace g3
