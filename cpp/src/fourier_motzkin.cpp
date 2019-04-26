//fourier_motzkin.cpp

#include "fourier_motzkin.h"
//Fourier Motzkin Elimination

#include <algorithm>

using namespace std;

// keep only the first d elements of each vector
// (get d from common.h)
Matrix project_matrix(const Matrix &M) {
  Matrix result;
  for (auto &&row : M) {
    result.emplace_back(d);
    copy_n(begin(row), d, begin(result.back()));
  }
  return result;
}

// Fourier Motzkin Elimation on index k
Matrix fourier_motzkin(Matrix M, size_t k) {
  Matrix result;
  // Partition into Z,P,N
  const auto z_end = partition(M.begin(),M.end(),
      [k](const Vector &v) { return v[k] == 0; });
  const auto p_end = partition(z_end, M.end(),
      [k](const Vector &v) { return v[k] > 0; });
  // Move Z to result
  move(M.begin(), z_end, back_inserter(result));
  // convolute vectors from P,N
  for (auto p_it = z_end; p_it != p_end; ++p_it) {
    for (auto z_it = p_end; z_it != M.end(); ++z_it) {
      result.push_back( 
        (*p_it)[k]*(*z_it) - (*z_it)[k]*(*p_it));
    } 
  } 
  return result;
}

