#include <iostream>
#include <random>

#include "g3/g3.h"

using namespace g3;

#define EXPECT_TRUE(EXPR)                                                      \
  if (!(EXPR)) {                                                               \
    std::cout << "\tTest failed: " #EXPR << std::endl;                         \
    return false;                                                              \
  }

#define EXPECT_EQ(EXPR1, EXPR2)                                                \
  if ((EXPR1) != (EXPR2)) {                                                    \
    std::cout << "\tEquality failed: " #EXPR1 " != " #EXPR2 << std::endl;      \
    std::cout << "\tLHS: " << (EXPR1) << std::endl;                            \
    std::cout << "\tRHS: " << (EXPR2) << std::endl;                            \
    return false;                                                              \
  }

#define EXPECT_NEAR(EXPR1, EXPR2, TOL)                                         \
  if (((EXPR1) - (EXPR2)).norm() > TOL) {                                      \
    std::cout << "\tNearness failed: " #EXPR1 " not near " #EXPR2              \
              << std::endl;                                                    \
    std::cout << "\tLHS: " << (EXPR1) << std::endl;                            \
    std::cout << "\tRHS: " << (EXPR2) << std::endl;                            \
    std::cout << "\ttol: " << (TOL) << std::endl;                              \
    return false;                                                              \
  }

constexpr int kNumTrials = 100;
constexpr Scalar kTol = 1e-6;

#define TEST_INTRO(test_name)                                                  \
  {                                                                            \
    std::cout << "====Testing " #test_name << "====" << std::endl;             \
    bool failed = false;

#define TEST_OUTRO                                                             \
  if (failed) {                                                                \
    std::cout << "FAIL!!!!!!!!!!!!!!" << std::endl;                            \
  } else {                                                                     \
    std::cout << "OK" << std::endl;                                            \
  }                                                                            \
  }

#define RUN_RANDOM(test_name, engine)                                          \
  TEST_INTRO(test_name)                                                        \
  for (int i = 0; i < kNumTrials; ++i) {                                       \
    if (!test_##test_name(engine)) {                                           \
      failed = true;                                                           \
      break;                                                                   \
    }                                                                          \
  }                                                                            \
  TEST_OUTRO

#define RUN(test_name)                                                         \
  TEST_INTRO(test_name)                                                        \
  failed = !test_##test_name();                                                \
  TEST_OUTRO

template <typename T> T make_random(std::default_random_engine &engine) {
  T result;
  std::uniform_real_distribution<Scalar> unif(-100, 100);
  for (int i = 0; i < T::dimension; ++i) {
    result.data()[i] = unif(engine);
  }
  return result;
}

bool test_equals_operator(std::default_random_engine &engine) {
  const Vector vect = make_random<Vector>(engine);
  EXPECT_EQ(vect, vect);

  const Quaternion quat = make_random<Quaternion>(engine);
  EXPECT_EQ(quat, quat);

  const Multivector mvect = make_random<Multivector>(engine);
  EXPECT_EQ(mvect, mvect);

  return true;
}

bool test_minus_self_eq_zero(std::default_random_engine &engine) {
  const Vector vect = make_random<Vector>(engine);
  EXPECT_EQ(vect - vect, Vector::Zero());

  const Quaternion quat = make_random<Quaternion>(engine);
  EXPECT_EQ(quat - quat, Quaternion::Zero());

  const Multivector mvect = make_random<Multivector>(engine);
  EXPECT_EQ(mvect - mvect, Multivector::Zero());

  return true;
}

bool test_quaternion_mult_assoc(std::default_random_engine &engine) {
  const auto q1 = make_random<Quaternion>(engine);
  const auto q2 = make_random<Quaternion>(engine);
  const auto q3 = make_random<Quaternion>(engine);
  EXPECT_NEAR((q1 * q2) * q3, q1 * (q2 * q3), kTol);
  return true;
}

bool test_vector_vector_mult(std::default_random_engine &engine) {
  const Vector v1 = make_random<Vector>(engine);
  const Vector v2 = make_random<Vector>(engine);
  EXPECT_NEAR((v1 * v2) * v2, v1 * v2.norm_squared(), kTol);
  EXPECT_NEAR((v1 * (v2 * v2)), v1 * v2.norm_squared(), kTol);
  return true;
}

bool test_plus_self_eq_times_two(std::default_random_engine &engine) {
  const Vector vect = make_random<Vector>(engine);
  EXPECT_EQ(vect + vect, vect * 2.0);

  const Quaternion quat = make_random<Quaternion>(engine);
  EXPECT_EQ(quat + quat, quat * 2.0);

  const Multivector mvect = make_random<Multivector>(engine);
  EXPECT_EQ(mvect + mvect, mvect * 2.0);

  return true;
}

bool test_quaternion_ijk() {
  const auto i = Quaternion::FromInitializerList({0, 1, 0, 0});
  const auto j = Quaternion::FromInitializerList({0, 0, 1, 0});
  const auto k = Quaternion::FromInitializerList({0, 0, 0, 1});

  EXPECT_EQ(i * j, k);
  EXPECT_EQ(j * i, -k);

  EXPECT_EQ(j * k, i);
  EXPECT_EQ(k * j, -i);

  EXPECT_EQ(k * i, j);
  EXPECT_EQ(i * k, -j);

  return true;
}

bool test_distributivity(std::default_random_engine &engine) {
  const Quaternion q1 = make_random<Quaternion>(engine);
  const Quaternion q2 = make_random<Quaternion>(engine);
  const Quaternion q3 = make_random<Quaternion>(engine);
  const Vector v1 = make_random<Vector>(engine);
  const Vector v2 = make_random<Vector>(engine);
  const Vector v3 = make_random<Vector>(engine);
  const Multivector m1 = make_random<Multivector>(engine);
  const Multivector m2 = make_random<Multivector>(engine);
  const Multivector m3 = make_random<Multivector>(engine);

  EXPECT_NEAR(q1 * (q2 + q3), q1 * q2 + q1 * q3, kTol);
  EXPECT_NEAR((q2 + q3) * q1, q2 * q1 + q3 * q1, kTol);
  EXPECT_NEAR(v1 * (v2 + v3), v1 * v2 + v1 * v3, kTol);
  EXPECT_NEAR((v2 + v3) * v1, v2 * v1 + v3 * v1, kTol);
  EXPECT_NEAR(m1 * (m2 + m3), m1 * m2 + m1 * m3, kTol);
  EXPECT_NEAR((m2 + m3) * m1, m2 * m1 + m3 * m1, kTol);
  EXPECT_NEAR(v1 * (q2 + q3), v1 * q2 + v1 * q3, kTol);
  EXPECT_NEAR((q2 + q3) * v1, q2 * v1 + q3 * v1, kTol);

  return true;
}

bool test_mult_divide_by_scalar(std::default_random_engine &engine) {
  const Quaternion q = make_random<Quaternion>(engine);
  const Vector v = make_random<Vector>(engine);
  const Multivector m = make_random<Multivector>(engine);
  EXPECT_NEAR(q, (q * 5.0) / 5.0, kTol);
  EXPECT_NEAR(v, (v * 5.0) / 5.0, kTol);
  EXPECT_NEAR(m, (m * 5.0) / 5.0, kTol);
  return true;
}

bool test_inverse(std::default_random_engine &engine) {
  const auto v = make_random<Vector>(engine);
  const auto q = make_random<Quaternion>(engine);
  const auto b = make_random<Bivector>(engine);
  EXPECT_NEAR(v * v.inverted(), Quaternion::FromScalar(1), kTol);
  EXPECT_NEAR(q * q.inverted(), Quaternion::FromScalar(1), kTol);
  EXPECT_NEAR(b * b.inverted(), Quaternion::FromScalar(1), kTol);
  return true;
}

bool test_divide_vs_inverse(std::default_random_engine &engine) {
  const auto v = make_random<Vector>(engine);
  const auto q = make_random<Quaternion>(engine);
  const auto b = make_random<Bivector>(engine);
  EXPECT_EQ(v / q, v * q.inverted())
  EXPECT_EQ(q / b, q * b.inverted())
  EXPECT_EQ(b / v, b * v.inverted())
  return true;
}

bool test_to_from_multivector(std::default_random_engine &engine) {
  const auto v = make_random<Vector>(engine);
  const auto q = make_random<Quaternion>(engine);
  const auto b = make_random<Bivector>(engine);

  EXPECT_EQ(Multivector::From(v).get<Vector>(), v);
  EXPECT_EQ(Multivector::From(q).get<Quaternion>(), q);
  EXPECT_EQ(Multivector::From(b).get<Bivector>(), b);
  EXPECT_EQ(Multivector::From(q).get<Vector>(), Vector::Zero());

  return true;
}

bool test_quaternion_bivector(std::default_random_engine &engine) {
  const auto q = make_random<Quaternion>(engine);
  const auto b = Multivector::From(q).get<Bivector>();
  const Scalar s = q.s();
  EXPECT_EQ(s + b, q);
  return true;
}

int main(int argc, char **argv) {
  std::cout << "Running tests" << std::endl;
  std::default_random_engine engine;

  RUN_RANDOM(distributivity, engine);
  RUN_RANDOM(divide_vs_inverse, engine);
  RUN_RANDOM(equals_operator, engine);
  RUN_RANDOM(inverse, engine);
  RUN_RANDOM(minus_self_eq_zero, engine);
  RUN_RANDOM(mult_divide_by_scalar, engine);
  RUN_RANDOM(plus_self_eq_times_two, engine);
  RUN_RANDOM(quaternion_bivector, engine);
  RUN_RANDOM(quaternion_mult_assoc, engine);
  RUN_RANDOM(to_from_multivector, engine);
  RUN_RANDOM(vector_vector_mult, engine);
  RUN(quaternion_ijk);

  return 0;
}
