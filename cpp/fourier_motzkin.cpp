//fourier_motzkin.cpp

#include "fourier_motzkin.h"
//Fourier Motzkin Elimination (fme)

#include <algorithm>
#include <iostream>

using namespace std;

size_t d;
size_t p;

/* represent vcone as projection of hcone
 *             d  p
 *    p     p| 0 -I|
 * d |U| -> d| I -U|
 *          d|-I  U|
 */
Matrix lift_vcone(const Matrix &m) {
  Matrix result;
  for (size_t i = 0; i < p; ++i) {
    result.emplace_back(d+p);
    result.back()[d+i] = -1;
  }
  size_t row_i = 0;
  for (auto &&row : m) {
    result.emplace_back(d+p);
    result.back()[row_i++] = -1;
    copy(begin(row),end(row),next(begin(result.back()),d));
    result.back() *= -1;
  }
  row_i = 0;
  for (auto &&row : m) {
    result.emplace_back(d+p);
    result.back()[row_i++] = -1;
    copy(begin(row),end(row),next(begin(result.back()),d));
  }
  return result;
}

// Fourier Motzkin Elimation on index k
Matrix fme(Matrix m, size_t k) {
  Matrix result;
  const auto z_end = partition(m.begin(),m.end(),
      [k](const Vector &v) { return v[k] == 0; });
  const auto p_end = partition(z_end, m.end(),
      [k](const Vector &v) { return v[k] > 0; });
  move(m.begin(), z_end, back_inserter(result));
  for (auto p_it = z_end; p_it != p_end; ++p_it) {
    for (auto z_it = p_end; z_it != m.end(); ++z_it) {
      result.push_back( (*p_it)[k]*(*z_it) - (*z_it)[k]*(*p_it) );
    }
  }
  return result;
}

// keep only the first d elements of each vector
Matrix project_matrix(const Matrix &m) {
  Matrix result;
  for (auto &&row : m) {
    result.emplace_back(d);
    copy_n(begin(row), d, begin(result.back()));
  }
  return result;
}

/* fme from d+1 to p,
 * project away d+1 to p
 */
Matrix project_hcone(Matrix &&m) {
  Matrix result = move(m);
  for (size_t i = d; i < d+p; ++i) {
    result = fme(move(result), i);
  }
  result = project_matrix(result);
  return result;
}

Matrix lift_hcone(const Matrix &m) {
  Matrix result;
  return result;
}

Matrix intersect_vcone(const Matrix &m) {
  Matrix result;
  return result;
}

Matrix project_vcone(const Matrix &m) {
  Matrix result;
  return result;
}

Matrix vcone_to_hcone(const Matrix &m) {
  Matrix result;
  if (m.empty() || !m.front().size()) {
    throw logic_error{"empty vcone"};
  }
  p = m.size();
  d = m.front().size();
  result = lift_vcone(m);
  result = project_hcone(move(result));
  return result;
}

Matrix hcone_to_vcone(const Matrix &m) {
  Matrix result;
  result = lift_hcone(m);
  result = intersect_vcone(result);
  result = project_vcone(result);
  return result;
}
