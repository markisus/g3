#include <random>
#include <time.h>

#include "g3/multivector_layout.h"
#include "g3/quaternion_layout.h"
#include "g3/unrolled_add.h"
#include "g3/unrolled_multiply.h"
#include "g3/vector_layout.h"

using namespace g3;

constexpr int num_trials = 10000000;

#define DEFINE_TIME_FUNC(FUNC)                                                 \
  template <bool unrolled, typename TLayoutA, typename TLayoutB,               \
            typename TLayoutC>                                                 \
  inline double time_##FUNC(const Scalar *as, const Scalar *bs, Scalar *cs) {  \
    const clock_t t1 = clock();                                                \
    for (int i = 0; i < num_trials; ++i) {                                     \
      const Scalar *a = &as[i * TLayoutA::dimension];                          \
      const Scalar *b = &bs[i * TLayoutB::dimension];                          \
      Scalar *c = &cs[i * TLayoutC::dimension];                                \
      if (unrolled) {                                                          \
        unrolled_##FUNC<TLayoutA, TLayoutB, TLayoutC>(a, b, c);                \
      } else {                                                                 \
        rolled_##FUNC<TLayoutA, TLayoutB, TLayoutC>(a, b, c);                  \
      }                                                                        \
    }                                                                          \
    const clock_t t2 = clock();                                                \
    return 1e6 * (double(t2 - t1) / CLOCKS_PER_SEC) / num_trials;              \
  }

DEFINE_TIME_FUNC(multiply)
DEFINE_TIME_FUNC(add)

template <typename TLayout>
std::vector<Scalar> get_random_trials(std::default_random_engine &engine) {
  std::uniform_real_distribution<Scalar> unif(-100, 100);
  std::vector<Scalar> trials;
  for (int i = 0; i < num_trials; ++i) {
    for (int j = 0; j < TLayout::dimension; ++j) {
      trials.push_back(unif(engine));
    }
  }
  return trials;
}

template <typename TLayout> std::vector<Scalar> get_trials_output_buffer() {
  std::vector<Scalar> buff(TLayout::dimension * num_trials);
  return buff;
}

#define DEFINE_TEST_FUNC(FUNC)                                                 \
  template <typename TLayoutA, typename TLayoutB, typename TLayoutC>           \
  void test_##FUNC(std::default_random_engine &engine) {                       \
    std::cout << "Testing " #FUNC << std::endl;                                \
    const std::vector<Scalar> as = get_random_trials<TLayoutA>(engine);        \
    const std::vector<Scalar> bs = get_random_trials<TLayoutB>(engine);        \
    std::vector<Scalar> c1s = get_trials_output_buffer<TLayoutC>();            \
    std::vector<Scalar> c2s = get_trials_output_buffer<TLayoutC>();            \
                                                                               \
    const double unrolled_time =                                               \
        time_##FUNC<true, TLayoutA, TLayoutB, TLayoutC>(as.data(), bs.data(),  \
                                                        c1s.data());           \
    const double rolled_time =                                                 \
        time_##FUNC<false, TLayoutA, TLayoutB, TLayoutC>(as.data(), bs.data(), \
                                                         c2s.data());          \
                                                                               \
    std::cout << TLayoutA::name << " x " << TLayoutB::name << " -> "           \
              << TLayoutC::name << std::endl;                                  \
    std::cout << "Unrolled time " << unrolled_time << " usec/trial"            \
              << std::endl;                                                    \
    std::cout << "Rolled time " << rolled_time << " usec/trial" << std::endl;  \
                                                                               \
    for (size_t i = 0; i < c1s.size(); ++i) {                                  \
      if (c1s[i] != c2s[i]) {                                                  \
        std::cout << "Error, unrolled != rolled" << std::endl;                 \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
    std::cout << std::endl;                                                    \
  }

DEFINE_TEST_FUNC(add)
DEFINE_TEST_FUNC(multiply)

int main(int argc, char **argv) {
  std::default_random_engine engine;

  bool do_test_multiply = true;
  bool do_test_add = true;

  if (do_test_multiply) {
    test_multiply<MultivectorLayout, MultivectorLayout, MultivectorLayout>(
        engine);
    test_multiply<MultivectorLayout, QuaternionLayout, MultivectorLayout>(
        engine);
    test_multiply<MultivectorLayout, VectorLayout, MultivectorLayout>(engine);
    test_multiply<QuaternionLayout, MultivectorLayout, MultivectorLayout>(
        engine);
    test_multiply<QuaternionLayout, VectorLayout, MultivectorLayout>(engine);
    test_multiply<QuaternionLayout, VectorLayout, QuaternionLayout>(engine);
    test_multiply<VectorLayout, MultivectorLayout, MultivectorLayout>(engine);
    test_multiply<VectorLayout, QuaternionLayout, MultivectorLayout>(engine);
    test_multiply<VectorLayout, QuaternionLayout, QuaternionLayout>(engine);
    test_multiply<VectorLayout, VectorLayout, MultivectorLayout>(engine);
    test_multiply<VectorLayout, VectorLayout, QuaternionLayout>(engine);
  }

  if (do_test_add) {
    test_add<MultivectorLayout, MultivectorLayout, MultivectorLayout>(engine);
    test_add<MultivectorLayout, QuaternionLayout, MultivectorLayout>(engine);
    test_add<MultivectorLayout, VectorLayout, MultivectorLayout>(engine);
    test_add<QuaternionLayout, MultivectorLayout, MultivectorLayout>(engine);
    test_add<QuaternionLayout, QuaternionLayout, QuaternionLayout>(engine);
    test_add<QuaternionLayout, VectorLayout, MultivectorLayout>(engine);
    test_add<QuaternionLayout, VectorLayout, QuaternionLayout>(engine);
    test_add<VectorLayout, QuaternionLayout, MultivectorLayout>(engine);
    test_add<VectorLayout, QuaternionLayout, QuaternionLayout>(engine);
    test_add<VectorLayout, VectorLayout, MultivectorLayout>(engine);
    test_add<VectorLayout, VectorLayout, QuaternionLayout>(engine);
    test_add<VectorLayout, VectorLayout, VectorLayout>(engine);
  }

  return 0;
}
