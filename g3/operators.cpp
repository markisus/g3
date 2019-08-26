#include "g3/bivector.h"
#include "g3/multivector.h"
#include "g3/operators.h"
#include "g3/quaternion.h"
#include "g3/vector.h"

namespace g3 {

#define G3_DEFINE_MULTIPLY(T1, T2, TResult)                                    \
  TResult operator*(const T1 &a, const T2 &b) {                                \
    TResult result;                                                            \
    multiply<T1::layout_type, T2::layout_type, TResult::layout_type>(          \
        a.data(), b.data(), result.data());                                    \
    return result;                                                             \
  }

#define G3_DEFINE_MULTIPLY_SYMMETRIC(T1, T2, TResult)                          \
  G3_DEFINE_MULTIPLY(T1, T2, TResult)                                          \
  G3_DEFINE_MULTIPLY(T2, T1, TResult)

#define G3_DEFINE_MULTIPLY_ASSIGN(T1, T2)                                      \
  T1 &operator*=(T1 &a, const T2 &b) {                                         \
    multiply<T1::layout_type, T2::layout_type, T1::layout_type>(               \
        a.data(), b.data(), a.data());                                         \
    return a;                                                                  \
  }

#define G3_DEFINE_DIVIDE(T1, T2, TResult)                                      \
  TResult operator/(const T1 &a, const T2 &b) {                                \
    TResult result;                                                            \
    multiply<T1::layout_type, T2::layout_type, TResult::layout_type>(          \
        a.data(), b.inverted().data(), result.data());                         \
    return result;                                                             \
  }

#define G3_DEFINE_DIVIDE_ASSIGN(T1, T2)                                        \
  T1 &operator/=(T1 &a, const T2 &b) {                                         \
    multiply<T1::layout_type, T2::layout_type, T1::layout_type>(               \
        a.data(), b.inverted().data(), a.data());                              \
    return a;                                                                  \
  }

#define G3_DEFINE_SCALAR_ADD_SUBTRACT(T, TResult)                              \
  TResult operator+(const T &t, Scalar a) {                                    \
    auto result = TResult::Zero();                                             \
    result += t; /* "cast" t to the result type (e.g. the case where T is      \
                    Bivector and TResult is Quaternion */                      \
    result.data()[0] += a; /* 0th entry is always the scalar entry for those   \
                              classes that have one */                         \
    return result;                                                             \
  }                                                                            \
  TResult operator+(Scalar a, const T &t) { return t + a; }                    \
  TResult operator-(const T &t, Scalar a) { return t + (-a); }                 \
  TResult operator-(Scalar a, const T &t) { return t + (-a); }

#define G3_DEFINE_SCALAR_ADD_SUBTRACT_ASSIGN(T)                                \
  T &operator+=(T &t, Scalar a) {                                              \
    t = (t + a);                                                               \
    return t;                                                                  \
  }                                                                            \
  T &operator-=(T &t, Scalar a) {                                              \
    t = (t - a);                                                               \
    return t;                                                                  \
  }

#define G3_DEFINE_ADD_SUBTRACT(T1, T2, TResult)                                \
  TResult operator+(const T1 &t1, const T2 &t2) {                              \
    TResult result;                                                            \
    add<T1::layout_type, T2::layout_type, TResult::layout_type>(               \
        t1.data(), t2.data(), result.data());                                  \
    return result;                                                             \
  }                                                                            \
  TResult operator-(const T1 &t1, const T2 &t2) {                              \
    TResult result;                                                            \
    const T2 neg_t2 = -t2;                                                     \
    add<T1::layout_type, T2::layout_type, TResult::layout_type>(               \
        t1.data(), neg_t2.data(), result.data());                              \
    return result;                                                             \
  }

#define G3_DEFINE_ADD_SUBTRACT_SYMMETRIC(T1, T2, TResult)                      \
  G3_DEFINE_ADD_SUBTRACT(T1, T2, TResult)                                      \
  G3_DEFINE_ADD_SUBTRACT(T2, T1, TResult)

#define G3_DEFINE_ADD_SUBTRACT_ASSIGN(T1, T2)                                  \
  T1 operator+=(T1 &t1, const T2 &t2) {                                        \
    t1 = t1 + t2;                                                              \
    return t1;                                                                 \
  }                                                                            \
  T1 operator-=(T1 &t1, const T2 &t2) {                                        \
    t1 = t1 - t2;                                                              \
    return t1;                                                                 \
  };

G3_DEFINE_ADD_SUBTRACT_ASSIGN(Multivector, Bivector)
G3_DEFINE_ADD_SUBTRACT_ASSIGN(Multivector, Quaternion)
G3_DEFINE_ADD_SUBTRACT_ASSIGN(Multivector, Vector)
G3_DEFINE_ADD_SUBTRACT_ASSIGN(Quaternion, Bivector)
G3_DEFINE_ADD_SUBTRACT_SYMMETRIC(Bivector, Multivector, Multivector)
G3_DEFINE_ADD_SUBTRACT_SYMMETRIC(Bivector, Quaternion, Quaternion)
G3_DEFINE_ADD_SUBTRACT_SYMMETRIC(Quaternion, Multivector, Multivector)
G3_DEFINE_ADD_SUBTRACT_SYMMETRIC(Vector, Bivector, Multivector)
G3_DEFINE_ADD_SUBTRACT_SYMMETRIC(Vector, Multivector, Multivector)
G3_DEFINE_ADD_SUBTRACT_SYMMETRIC(Vector, Quaternion, Multivector)
G3_DEFINE_DIVIDE(Bivector, Bivector, Quaternion)
G3_DEFINE_DIVIDE(Bivector, Quaternion, Quaternion)
G3_DEFINE_DIVIDE(Bivector, Vector, Vector)
G3_DEFINE_DIVIDE(Multivector, Bivector, Multivector)
G3_DEFINE_DIVIDE(Multivector, Quaternion, Multivector)
G3_DEFINE_DIVIDE(Multivector, Vector, Multivector)
G3_DEFINE_DIVIDE(Quaternion, Bivector, Quaternion)
G3_DEFINE_DIVIDE(Quaternion, Quaternion, Quaternion)
G3_DEFINE_DIVIDE(Quaternion, Vector, Vector)
G3_DEFINE_DIVIDE(Vector, Bivector, Vector)
G3_DEFINE_DIVIDE(Vector, Quaternion, Vector)
G3_DEFINE_DIVIDE(Vector, Vector, Quaternion)
G3_DEFINE_DIVIDE_ASSIGN(Multivector, Bivector)
G3_DEFINE_DIVIDE_ASSIGN(Multivector, Quaternion)
G3_DEFINE_DIVIDE_ASSIGN(Multivector, Vector)
G3_DEFINE_DIVIDE_ASSIGN(Quaternion, Bivector)
G3_DEFINE_DIVIDE_ASSIGN(Quaternion, Quaternion)
G3_DEFINE_DIVIDE_ASSIGN(Vector, Bivector)
G3_DEFINE_DIVIDE_ASSIGN(Vector, Quaternion)
G3_DEFINE_MULTIPLY(Bivector, Bivector, Quaternion)
G3_DEFINE_MULTIPLY(Multivector, Multivector, Multivector)
G3_DEFINE_MULTIPLY(Quaternion, Quaternion, Quaternion)
G3_DEFINE_MULTIPLY(Vector, Vector, Quaternion)
G3_DEFINE_MULTIPLY_ASSIGN(Multivector, Bivector)
G3_DEFINE_MULTIPLY_ASSIGN(Multivector, Multivector)
G3_DEFINE_MULTIPLY_ASSIGN(Multivector, Quaternion)
G3_DEFINE_MULTIPLY_ASSIGN(Multivector, Vector)
G3_DEFINE_MULTIPLY_ASSIGN(Quaternion, Bivector)
G3_DEFINE_MULTIPLY_ASSIGN(Quaternion, Quaternion)
G3_DEFINE_MULTIPLY_ASSIGN(Vector, Bivector)
G3_DEFINE_MULTIPLY_ASSIGN(Vector, Quaternion)
G3_DEFINE_MULTIPLY_SYMMETRIC(Bivector, Multivector, Multivector)
G3_DEFINE_MULTIPLY_SYMMETRIC(Bivector, Quaternion, Quaternion)
G3_DEFINE_MULTIPLY_SYMMETRIC(Quaternion, Multivector, Multivector)
G3_DEFINE_MULTIPLY_SYMMETRIC(Vector, Bivector, Vector)
G3_DEFINE_MULTIPLY_SYMMETRIC(Vector, Multivector, Multivector)
G3_DEFINE_MULTIPLY_SYMMETRIC(Vector, Quaternion, Vector)
G3_DEFINE_SCALAR_ADD_SUBTRACT(Bivector, Quaternion)
G3_DEFINE_SCALAR_ADD_SUBTRACT(Multivector, Multivector)
G3_DEFINE_SCALAR_ADD_SUBTRACT(Quaternion, Quaternion)
G3_DEFINE_SCALAR_ADD_SUBTRACT(Vector, Multivector)
G3_DEFINE_SCALAR_ADD_SUBTRACT_ASSIGN(Multivector)
G3_DEFINE_SCALAR_ADD_SUBTRACT_ASSIGN(Quaternion)

} // namespace g3
