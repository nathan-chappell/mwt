//hcone_to_hcone.cpp

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

// represent hcone as projection of hcone
//           d  d m
//   d     d|I -I 0|
// m|A| -> m|A -A I|
//
Matrix lift_hcone(const Matrix &hcone) {
  Matrix result;
  Matrix m_t = transpose(hcone);
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
Matrix intersect_vcone(Matrix &&vcone) {
  Matrix result = move(vcone);
  for (size_t i = d; i < d+m; ++i) {
    result = fourier_motzkin(move(result), i);
  }
  return project_matrix(result);
}

} //namespace

Matrix hcone_to_vcone(const Matrix &hcone) {
  if (check_empty_matrix(hcone)) {
    throw logic_error{"empty hcone"};
  }
  Matrix result;
  m = hcone.size();
  return HCone::intersect_vcone(HCone::lift_hcone(hcone));
}

int main() {
  Matrix hcone;
  cin >> hcone;
  cout << hcone_to_vcone(hcone);
}
