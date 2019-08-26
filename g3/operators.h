#pragma once

#include "g3/multiply.h"
#include "g3/scalar.h"

namespace g3 {
class Multivector;
class Vector;
class Quaternion;
class Bivector;

// See also the operators in multivector_base.h

#define G3_DECLARE_MULTIPLY(T1, T2, TResult)                                   \
  TResult operator*(const T1 &a, const T2 &b);

#define G3_DECLARE_MULTIPLY_SYMMETRIC(T1, T2, TResult)                         \
  G3_DECLARE_MULTIPLY(T1, T2, TResult)                                         \
  G3_DECLARE_MULTIPLY(T2, T1, TResult)

#define G3_DECLARE_DIVIDE(T1, T2, TResult)                                     \
  TResult operator/(const T1 &a, const T2 &b);

#define G3_DECLARE_MULTIPLY_ASSIGN(T1, T2) T1 &operator*=(T1 &a, const T2 &b);
#define G3_DECLARE_DIVIDE_ASSIGN(T1, T2) T1 &operator/=(T1 &a, const T2 &b);

#define G3_DECLARE_SCALAR_ADD_SUBTRACT(T, TResult)                             \
  TResult operator+(const T &t, Scalar a);                                     \
  TResult operator+(Scalar a, const T &t);                                     \
  TResult operator-(const T &t, Scalar a);                                     \
  TResult operator-(Scalar a, const T &t);

#define G3_DECLARE_SCALAR_ADD_SUBTRACT_ASSIGN(T)                               \
  T &operator+=(T &t, Scalar a);                                               \
  T &operator-=(T &t, Scalar a);

#define G3_DECLARE_ADD_SUBTRACT(T1, T2, TResult)                               \
  TResult operator+(const T1 &, const T2 &);                                   \
  TResult operator-(const T1 &, const T2 &);                                   \
  TResult operator+(const T2 &, const T1 &);                                   \
  TResult operator-(const T2 &, const T1 &);
#define G3_DECLARE_ADD_SUBTRACT_SYMMETRIC(T1, T2, TResult)                     \
  G3_DECLARE_ADD_SUBTRACT(T1, T2, TResult)                                     \
  G3_DECLARE_ADD_SUBTRACT(T2, T1, TResult)

#define G3_DECLARE_ADD_SUBTRACT_ASSIGN(T1, T2)                                 \
  T1 operator+=(T1 &, const T2 &);                                             \
  T1 operator-=(T1 &, const T2 &);

G3_DECLARE_ADD_SUBTRACT_ASSIGN(Multivector, Bivector)
G3_DECLARE_ADD_SUBTRACT_ASSIGN(Multivector, Quaternion)
G3_DECLARE_ADD_SUBTRACT_ASSIGN(Multivector, Vector)
G3_DECLARE_ADD_SUBTRACT_ASSIGN(Quaternion, Bivector)
G3_DECLARE_ADD_SUBTRACT_SYMMETRIC(Bivector, Multivector, Multivector)
G3_DECLARE_ADD_SUBTRACT_SYMMETRIC(Bivector, Quaternion, Quaternion)
G3_DECLARE_ADD_SUBTRACT_SYMMETRIC(Quaternion, Multivector, Multivector)
G3_DECLARE_ADD_SUBTRACT_SYMMETRIC(Vector, Bivector, Multivector)
G3_DECLARE_ADD_SUBTRACT_SYMMETRIC(Vector, Multivector, Multivector)
G3_DECLARE_ADD_SUBTRACT_SYMMETRIC(Vector, Quaternion, Multivector)
G3_DECLARE_DIVIDE(Bivector, Bivector, Quaternion)
G3_DECLARE_DIVIDE(Bivector, Quaternion, Quaternion)
G3_DECLARE_DIVIDE(Bivector, Vector, Vector)
G3_DECLARE_DIVIDE(Multivector, Bivector, Multivector)
G3_DECLARE_DIVIDE(Multivector, Quaternion, Multivector)
G3_DECLARE_DIVIDE(Multivector, Vector, Multivector)
G3_DECLARE_DIVIDE(Quaternion, Bivector, Quaternion)
G3_DECLARE_DIVIDE(Quaternion, Quaternion, Quaternion)
G3_DECLARE_DIVIDE(Quaternion, Vector, Vector)
G3_DECLARE_DIVIDE(Vector, Bivector, Vector)
G3_DECLARE_DIVIDE(Vector, Quaternion, Vector)
G3_DECLARE_DIVIDE(Vector, Vector, Quaternion)
G3_DECLARE_DIVIDE_ASSIGN(Multivector, Bivector)
G3_DECLARE_DIVIDE_ASSIGN(Multivector, Quaternion)
G3_DECLARE_DIVIDE_ASSIGN(Multivector, Vector)
G3_DECLARE_DIVIDE_ASSIGN(Quaternion, Bivector)
G3_DECLARE_DIVIDE_ASSIGN(Quaternion, Quaternion)
G3_DECLARE_DIVIDE_ASSIGN(Vector, Bivector)
G3_DECLARE_DIVIDE_ASSIGN(Vector, Quaternion)
G3_DECLARE_MULTIPLY(Bivector, Bivector, Quaternion)
G3_DECLARE_MULTIPLY(Multivector, Multivector, Multivector)
G3_DECLARE_MULTIPLY(Quaternion, Quaternion, Quaternion)
G3_DECLARE_MULTIPLY(Vector, Vector, Quaternion)
G3_DECLARE_MULTIPLY_ASSIGN(Multivector, Bivector)
G3_DECLARE_MULTIPLY_ASSIGN(Multivector, Multivector)
G3_DECLARE_MULTIPLY_ASSIGN(Multivector, Quaternion)
G3_DECLARE_MULTIPLY_ASSIGN(Multivector, Vector)
G3_DECLARE_MULTIPLY_ASSIGN(Quaternion, Bivector)
G3_DECLARE_MULTIPLY_ASSIGN(Quaternion, Quaternion)
G3_DECLARE_MULTIPLY_ASSIGN(Vector, Bivector)
G3_DECLARE_MULTIPLY_ASSIGN(Vector, Quaternion)
G3_DECLARE_MULTIPLY_SYMMETRIC(Bivector, Multivector, Multivector)
G3_DECLARE_MULTIPLY_SYMMETRIC(Bivector, Quaternion, Quaternion)
G3_DECLARE_MULTIPLY_SYMMETRIC(Quaternion, Multivector, Multivector)
G3_DECLARE_MULTIPLY_SYMMETRIC(Vector, Bivector, Vector)
G3_DECLARE_MULTIPLY_SYMMETRIC(Vector, Multivector, Multivector)
G3_DECLARE_MULTIPLY_SYMMETRIC(Vector, Quaternion, Vector)
G3_DECLARE_SCALAR_ADD_SUBTRACT(Bivector, Quaternion)
G3_DECLARE_SCALAR_ADD_SUBTRACT(Multivector, Multivector)
G3_DECLARE_SCALAR_ADD_SUBTRACT(Quaternion, Quaternion)
G3_DECLARE_SCALAR_ADD_SUBTRACT(Vector, Multivector)
G3_DECLARE_SCALAR_ADD_SUBTRACT_ASSIGN(Multivector)
G3_DECLARE_SCALAR_ADD_SUBTRACT_ASSIGN(Quaternion)

} // namespace g3
