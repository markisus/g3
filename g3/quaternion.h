#pragma once

#include "g3/multivector_base.h"
#include "g3/quaternion_layout.h"

namespace g3 {

class Quaternion : public MultivectorBase<Quaternion, QuaternionLayout> {
public:
  // Needed because functions do not overload across scopes
  using MultivectorBase<Quaternion, QuaternionLayout>::operator+;
  using MultivectorBase<Quaternion, QuaternionLayout>::operator*;
  using MultivectorBase<Quaternion, QuaternionLayout>::operator*=;
  using MultivectorBase<Quaternion, QuaternionLayout>::operator/;
  using MultivectorBase<Quaternion, QuaternionLayout>::operator/=;

  static Quaternion FromScalar(Scalar s);

  Scalar s() const;
  Scalar i() const;
  Scalar j() const;
  Scalar k() const;

  Quaternion inverted() const;
  Quaternion &invert();

  Quaternion conjugated() const;
  Quaternion &conjugate();
};
} // namespace g3
