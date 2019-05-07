// fourier_motzkin.cpp

#include "fourier_motzkin.h"

#include <algorithm>
#include <iterator>

using namespace std;

// true iff index is "a member of" slice
bool index_in_slice(size_t index, const slice &s) {
  return ((index - s.start()) % s.stride() == 0) &&
          s.start() <= index && 
          index <= s.start() + s.stride()*(s.size()-1);
}

// Fourier Motzkin Elimation

// Fourier Motzkin Elimation on index k
Matrix fourier_motzkin(Matrix M, size_t k) {
  Matrix result{M.d};
  // Partition into Z,P,N
  const auto z_end = partition(M.begin(), M.end(),
      [k](const Vector &v) { return v[k] == 0; });
  const auto p_end = partition(z_end, M.end(),
      [k](const Vector &v) { return v[k] > 0; });
  // Move Z to result
  move(M.begin(), z_end, back_inserter(result));
  // convolute vectors from P,N
  for (auto p_it = z_end; p_it != p_end; ++p_it) {
    for (auto n_it = p_end; n_it != M.end(); ++n_it) {
      result.push_back( 
        (*p_it)[k]*(*n_it) - (*n_it)[k]*(*p_it));
    } 
  } 
  return result;
}

// Fourier Motzkin, on each index not in slice, then slice the result
Matrix sliced_fourier_motzkin(Matrix M, const slice &s) {
  for (size_t k = 0; k < M.d; ++k) {
    if (!index_in_slice(k,s)) {
      M = fourier_motzkin(M, k);
    }
  }
  return slice_matrix(M, s);
}

// refactored lift operation
//
//  transforms set of column vectors as so:
//
//            ___d__ ___n__
//   n     n|     0 C[0]*I|
// d|U| -> d|C[1]*I C[2]*U|
//         d|C[3]*I C[4]*U|
//
//  transforms set of row vectors as so:
//
//           ___n__ ___d__ ___d__
//   d     d|     0 C[1]*I C[3]*I|
// n|A| -> n|C[0]*I C[2]*A C[4]*A|
//
Matrix generalized_lift(const Matrix &cone, 
                        const array<double,5> &C) {
  const size_t d = cone.d;
  const size_t n = cone.size();
  Matrix result{d+n};
  Matrix cone_t = transpose(cone);
  // |0  C[0]*I|  |0     |
  //              |C[0]*I|
  for (size_t i = 0; i < n; ++i) {
    result.add_Vector()[d+i] = C[0];
  }
  size_t k = 0;
  // |C[1]*I C[2]*U|  |C[1]*I|
  //                  |C[2]*A|
  for (auto &&row_t : cone_t) {
    result.push_back(
      concatenate(C[1]*e_k(d,k++), C[2]*row_t));
  }
  k = 0;
  // |C[3]*I C[4]*U|  |C[3]*I|
  //                  |C[4]*A|
  for (auto &&row_t : cone_t) {
    result.push_back(
      concatenate(C[3]*e_k(d,k++), C[4]*row_t));
  }
  return result;
}

// represent vcone as projection of hcone
//             d  p
//    p     p| 0 -I|
// d |U| -> d| I -U|
//          d|-I  U|
//
Matrix lift_vcone(const Matrix &vcone) {
  return generalized_lift(vcone, {-1,1,-1,-1,1});
}

// represent hcone as projection of vcone
//           m d  d
//   d     d|0 I -I|
// m|A| -> m|I A -A|
//
Matrix lift_hcone(const Matrix &hcone) {
  return generalized_lift(hcone, {1,1,1,-1,-1});
}

// refactored transformation algorithm
Matrix cone_transform(const Matrix &cone, LiftSelector lift) {
  if (cone.empty()) {
    throw logic_error{"empty cone for transform"};
  }
  switch (lift) {
    case LiftSelector::lift_vcone: {
      return sliced_fourier_motzkin(
        lift_vcone(cone), slice(0, cone.d, 1));
    } break;
    case LiftSelector::lift_hcone: {
      return sliced_fourier_motzkin(
        lift_hcone(cone), slice(0, cone.d, 1));
    } break;
    default: {
      throw std::logic_error{"invalid LiftSelector"};
    }
  }
}

Matrix vcone_to_hcone(Matrix vcone) {
  return cone_transform(vcone,LiftSelector::lift_vcone);
}

Matrix hcone_to_vcone(Matrix hcone) {
  return cone_transform(hcone,LiftSelector::lift_hcone);
}
