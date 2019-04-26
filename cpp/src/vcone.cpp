//vcone.cpp

#include "vcone.h"
#include "fourier_motzkin.h"

#include <algorithm>
#include <iostream>

using namespace std;

//number of generators in cone
size_t p;

// V-Cone -> H-Cone operations
namespace VCone {
//the operations in this namespace should not modify these values
const size_t &d{::d};
const size_t &p{::p};

// represent vcone as projection of hcone
//             d  p
//    p     p| 0 -I|
// d |U| -> d| I -U|
//          d|-I  U|
//
Matrix lift_vcone(const Matrix &vcone) {
  Matrix result;
  Matrix m_t = transpose(vcone);
  //| 0 -I|
  for (size_t i = 0; i < p; ++i) {
    result.emplace_back(d+p);
    result.back()[d+i] = -1;
  }
  size_t column_i = 0;
  //|-I  U|
  for (auto &&row_t : m_t) {
    result.emplace_back(d+p);
    result.back()[column_i++] = -1;
    copy(begin(row_t),end(row_t),next(begin(result.back()),d));
  }
  column_i = 0;
  //| I -U|
  for (auto &&row_t : m_t) {
    result.emplace_back(d+p);
    result.back()[column_i++] = -1;
    copy(begin(row_t),end(row_t),next(begin(result.back()),d));
    result.back() *= -1;
  }
  return result;
}

// project away d+1 to p
Matrix project_hcone(Matrix &&hcone) {
  Matrix result = move(hcone);
  for (size_t i = d; i < d+p; ++i) {
    result = fourier_motzkin(move(result), i);
  }
  return project_matrix(result);
}

} //namespace

Matrix vcone_to_hcone(Matrix vcone) {
  if (check_empty_matrix(vcone)) {
    throw logic_error{"empty vcone"};
  }
  p = vcone.size();
  return VCone::project_hcone(VCone::lift_vcone(vcone));
}