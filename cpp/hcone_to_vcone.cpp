//hcone_to_hone.cpp

#include "common.h"
#include "fourier_motzkin.h"

#include <algorithm>
#include <iostream>

using namespace std;

//number of generators in cone
size_t m;

// V-Cone -> H-Cone operations
namespace HCone {
//the operations in this namespace should not modify these values
const size_t &d{::d};
const size_t &m{::m};

// represent hone as projection of hcone
//           d  d m
//   d     d|I -I 0|
// m|A| -> m|A -A I|
//
Matrix lift_hcone(const Matrix &M) {
  Matrix result;
  Matrix m_t = transpose(M);
  //|I|
  //|A|
  size_t k{0};
  for (auto &&row : m_t) {
    result.emplace_back(d+m);
    result.back()[k++] = 1;
    copy(begin(row), end(row), next(begin(result.back()), d));
  }
  //|-I|
  //|-A|
  k = 0;
  for (auto &&row : m_t) {
    result.emplace_back(d+m);
    result.back()[k++] = 1;
    copy(begin(row), end(row), next(begin(result.back()), d));
    result.back() *= -1;
  }
  //|0|
  //|I|
  for (size_t i = 0; i < m; ++i) {
    result.emplace_back(d+m);
    result.back()[d+i] = 1;
  }
  return result;
}

// intersect vcone with {x_k = 0 | d+1 <= k <= d+m}
Matrix intersect_vcone(Matrix &&M) {
  Matrix result = move(M);
  for (size_t i = d; i < d+m; ++i) {
    result = fourier_motzkin(move(result), i);
  }
  return project_matrix(result);
}

} //namespace

Matrix hone_to_vcone(const Matrix &M) {
  if (check_empty_matrix(M)) {
    throw logic_error{"empty hone"};
  }
  Matrix result;
  m = M.size();
  return HCone::intersect_vcone(HCone::lift_hcone(M));
}

int main() {
  Matrix hone;
  cin >> hone;
  Matrix hcone = hone_to_vcone(hone);
  cout << hcone;
}
