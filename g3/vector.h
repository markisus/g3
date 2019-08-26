#pragma once

#include "g3/multivector.h"
#include "g3/multivector_base.h"
#include "g3/quaternion.h"
#include "g3/vector_layout.h"
#include "g3/operators.h"

namespace g3 {

class Vector : public MultivectorBase<Vector, VectorLayout> {
 public:
  // Needed because functions do not overload across scopes
  using MultivectorBase<Vector, VectorLayout>::operator*;
  using MultivectorBase<Vector, VectorLayout>::operator*=;
  using MultivectorBase<Vector, VectorLayout>::operator/;
  using MultivectorBase<Vector, VectorLayout>::operator/=;

  Scalar x() const;
  Scalar y() const;
  Scalar z() const;
  
  Vector inverted() const;
  Vector &invert();
};

} // namespace g3
