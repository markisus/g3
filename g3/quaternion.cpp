#include "g3/quaternion.h"

namespace g3 {

Quaternion Quaternion::FromScalar(Scalar s) {
  return FromInitializerList({1, 0, 0, 0});
}

Scalar Quaternion::s() const { return data()[0]; }
Scalar Quaternion::i() const { return data()[1]; }
Scalar Quaternion::j() const { return data()[2]; }
Scalar Quaternion::k() const { return data()[3]; }

Quaternion &Quaternion::conjugate() {
  for (size_t i = 1; i < 4; ++i) {
    data()[i] *= -1;
  }
  return *this;
}

Quaternion Quaternion::conjugated() const {
  Quaternion this_copy = *this;
  this_copy.conjugate();
  return this_copy;
}

Quaternion Quaternion::inverted() const {
  // q q.conjugated = q.norm_squared()
  // q * (q.conjuaged / q.norm_squared()) = 1.0
  Quaternion result = *this;
  result.conjugate();
  result /= result.norm_squared();
  return result;
}

Quaternion &Quaternion::invert() {
  *this = inverted();
  return *this;
}

} // namespace g3
