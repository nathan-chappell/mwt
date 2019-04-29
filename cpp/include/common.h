//common.h
#pragma once

#include <array>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <valarray>
#include <vector>

using Vector = std::valarray<double>;
using Vectors = std::vector<Vector>;

// Vector utilities

// basis vectors
Vector e_k(size_t d, size_t k, double v = 1);

// concatentation
Vector concatenate(const Vector &l, const Vector &r);

struct Matrix {
  const size_t d; // size of all Vectors
  Vectors vectors;

  Matrix(size_t d) : d{d} { 
    if (d == 0) throw std::logic_error{"no 0-d matrices!"};
  }

  static Matrix read_Matrix(std::istream&);

  Vectors::iterator       begin()       { return vectors.begin(); }
  Vectors::iterator       end()         { return vectors.end(); }
  Vectors::const_iterator begin() const { return vectors.begin(); }
  Vectors::const_iterator end()   const { return vectors.end(); }

  size_t  size() const { return vectors.size(); }
  Vector& back()       { return vectors.back(); }

  Vector& add_Vector() { vectors.emplace_back(d); return vectors.back(); }
  void push_back(const Vector &v);
  void push_back(Vector &&v);
};

struct VPoly {
  const size_t d;
  Matrix U; // rays
  Matrix V; // points

  VPoly(size_t d) : d{d}, U{d}, V{d} {}
  static VPoly read_VPoly(std::istream&);
};

std::istream& operator>>(std::istream&, Vector&);
std::istream& operator>>(std::istream&, Matrix&);
std::istream& operator>>(std::istream&, VPoly&);

std::ostream& operator<<(std::ostream& o, const Vector&);
std::ostream& operator<<(std::ostream& o, const Matrix&);
std::ostream& operator<<(std::ostream& o, const VPoly&);

class input_error : public std::runtime_error {
public:
  input_error(const char*s) : std::runtime_error{s} {}
  input_error(const std::string &s) : std::runtime_error{s} {}
};

int usage();

// Matrix utilities

Matrix transpose(Matrix M);

// slice each Vector of the Matrix and return the result
Matrix slice_matrix(const Matrix &, const std::slice&);

// Fourier Motzkin Elimination

// Fourier Motzkin Elimation on index k
Matrix fourier_motzkin(Matrix, size_t k);

// Fourier Motzkin for each index NOT in slice, then slice the result
Matrix sliced_fourier_motzkin(Matrix, const std::slice&);

// refactored lift operation, tranforms matrix as so:
//
//            __d__  __p___
//    p     p|    0  C[0]*I|
// d |U| -> d|C[1]*I C[2]*U|
//          d|C[3]*I C[4]*U|
//
Matrix generalized_lift(const Matrix &cone, const std::array<double,5> &C);

// represent vcone as projection of hcone
//             d  p
//    p     p| 0 -I|
// d |U| -> d| I -U|
//          d|-I  U|
//
Matrix lift_vcone(const Matrix &vcone);

// represent hcone as projection of vcone
//           m d  d
//   d     d|0 I -I|
// m|A| -> m|I A -A|
//
Matrix lift_hcone(const Matrix &hcone);

// refactored transformation algorithm
Matrix cone_transform(const Matrix &cone, 
                         Matrix(*lift)(const Matrix&));

// specific cone transforms
Matrix vcone_to_hcone(Matrix vcone);
Matrix hcone_to_vcone(Matrix hcone);

