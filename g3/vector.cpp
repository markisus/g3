#include "g3/vector.h"
#include "g3/multiply.h"
#include "g3/multivector.h"
#include "g3/quaternion.h"

namespace g3 {

Scalar Vector::x() const { return data()[0]; };
Scalar Vector::y() const { return data()[1]; };
Scalar Vector::z() const { return data()[2]; };

Vector Vector::inverted() const {
  Vector result = *this;
  result /= norm_squared();
  return result;
}

Vector &Vector::invert() {
  *this = inverted();
  return *this;
}

} // namespace g3
