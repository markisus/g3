#include "g3/bivector.h"

namespace g3 {

Scalar Bivector::i() const { return data()[0]; }
Scalar Bivector::j() const { return data()[1]; }
Scalar Bivector::k() const { return data()[2]; }

Bivector &Bivector::invert() {
  for (size_t i = 0; i < 3; ++i) {
    data()[i] *= -1;
  }
  *this /= norm_squared();
  return *this;
}

Bivector Bivector::inverted() const {
  Bivector this_copy = *this;
  this_copy.invert();
  return this_copy;
}

} // namespace g3
