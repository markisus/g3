#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>

#include "g3/add.h"
#include "g3/basis.h"
#include "g3/multiply.h"
#include "g3/scalar.h"

namespace g3 {

template <typename TChild, typename TLayout> class MultivectorBase {
public:
  using layout_type = TLayout;
  static constexpr uint8_t dimension = layout_type::dimension;

  static TChild Zero() {
    TChild result;
    for (int i = 0; i < TChild::dimension; ++i) {
      result.data()[i] = 0;
    }
    return result;
  }

  MultivectorBase() = default;

  static TChild FromData(const Scalar *data_start) {
    TChild result;
    for (int i = 0; i < TChild::dimension; ++i) {
      result.data()[i] = data_start[i];
    }
    return result;
  }

  static TChild
  FromInitializerList(const std::initializer_list<Scalar> &ilist) {
    TChild result;
    int idx = 0;
    for (Scalar s : ilist) {
      result.data()[idx] = s;
      ++idx;
    }
    return result;
  }

  Scalar *data() { return data_.data(); }

  const Scalar *data() const { return data_.data(); }

  bool operator==(const TChild &other) const {
    for (int i = 0; i < TChild::dimension; ++i) {
      if (this->data()[i] != other.data()[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const TChild &other) const { return !(*this == other); }

  Scalar &operator[](basis::Element e) {
    return data_[TChild::layout_type::basis_to_idx(e)];
  }

  const Scalar &operator[](basis::Element e) const {
    return data_[TChild::layout_type::basis_to_idx(e)];
  }

  TChild &operator*=(Scalar s) {
    for (int i = 0; i < TChild::dimension; ++i) {
      data_[i] *= s;
    }
    return static_cast<TChild &>(*this);
  }

  TChild &operator/=(Scalar s) {
    for (int i = 0; i < TChild::dimension; ++i) {
      data_[i] /= s;
    }
    return static_cast<TChild &>(*this);
  }

  TChild operator*(Scalar s) const {
    TChild this_copy = *static_cast<const TChild *>(this);
    this_copy *= s;
    return this_copy;
  }

  TChild operator/(Scalar s) const {
    TChild this_copy = *static_cast<const TChild *>(this);
    this_copy /= s;
    return this_copy;
  }

  TChild operator-() const { return (*this) * (-1.0); }

  TChild &operator+=(const TChild &other) {
    add_into<layout_type, layout_type>(other.data(), this->data());
    return static_cast<TChild &>(*this);
  }

  TChild &operator-=(const TChild &other) {
    add_into<layout_type, layout_type>((-other).data(), this->data());
    return static_cast<TChild &>(*this);
  }

  TChild operator+(const TChild &other) const {
    TChild this_copy = *static_cast<const TChild *>(this);
    this_copy += other;
    return this_copy;
  }

  TChild operator-(const TChild &other) const {
    TChild this_copy = *static_cast<const TChild *>(this);
    this_copy -= other;
    return this_copy;
  }

  Scalar norm_squared() const {
    Scalar acc = 0;
    for (int i = 0; i < layout_type::dimension; ++i) {
      acc += data_[i] * data_[i];
    }
    return acc;
  }

  Scalar norm() const { return std::sqrt(norm_squared()); }

  TChild normalized() const {
    TChild this_copy = *static_cast<const TChild *>(this);
    this_copy.normalize();
    return this_copy;
  }

  TChild &normalize() { *this /= norm(); }

private:
  std::array<Scalar, layout_type::dimension> data_;
};

template <typename TChild, typename TLayout>
std::ostream &operator<<(std::ostream &os,
                         const MultivectorBase<TChild, TLayout> &multivector) {
  os << "{";
  for (int idx = 0; idx < TLayout::dimension; ++idx) {
    const basis::Element e = TLayout::idx_to_basis[idx];
    os << multivector[e] << " " << e;
    if (idx != TLayout::dimension - 1) {
      os << ", ";
    }
  }
  os << "}";
  return os;
}

} // namespace g3
