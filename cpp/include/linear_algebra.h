// linear_algebra.h
#pragma once

#include <array>
#include <iostream>
#include <stdexcept>
#include <valarray>
#include <vector>

using Vector = std::valarray<double>;
using Vectors = std::vector<Vector>;

// invariant: d >= 0
// invariant: (forall valid i) vectors[i].size() == d
struct Matrix {
public:
  const size_t d; // size of all Vectors
private:
  Vectors vectors;
public:
  // needed for back_insert_iterator
  using value_type = Vector;

  Matrix(size_t d);
  Matrix(std::initializer_list<Vector>&&);
  bool check() const; // checks each Vector has size d

  //defaults don't work because of const member
  Matrix(const Matrix&);
  Matrix(Matrix&&);
  Matrix &operator=(const Matrix&);
  Matrix &operator=(Matrix&&);

  static Matrix read_Matrix(std::istream&);

  Vectors::iterator       begin()       { return vectors.begin(); }
  Vectors::iterator       end()         { return vectors.end(); }
  Vectors::const_iterator begin() const { return vectors.begin(); }
  Vectors::const_iterator end()   const { return vectors.end(); }

  bool    empty() const { return vectors.empty(); }
  size_t  size()  const { return vectors.size(); }
  Vector& back()        { return vectors.back(); }

  Vector& add_Vector() { vectors.emplace_back(d); return vectors.back(); }
  void push_back(const Vector &v);
  void push_back(Vector &&v);
};

struct VPoly {
  const size_t d;
  Matrix U; // rays
  Matrix V; // points

  VPoly(size_t d) : d{d}, U{d}, V{d} {}
  VPoly(std::initializer_list<Vector>&&, std::initializer_list<Vector>&&);
  bool check() const;

  static VPoly read_VPoly(std::istream&);
};

class input_error : public std::runtime_error {
public:
  input_error(const char*s) : std::runtime_error{s} {}
  input_error(const std::string &s) : std::runtime_error{s} {}
};

std::istream& operator>>(std::istream&, Vector&);
std::istream& operator>>(std::istream&, Matrix&);
std::istream& operator>>(std::istream&, VPoly&);

std::ostream& operator<<(std::ostream& o, const Vector&);
std::ostream& operator<<(std::ostream& o, const Matrix&);
std::ostream& operator<<(std::ostream& o, const VPoly&);

int usage();

// Vector utilities

// basis vectors
Vector e_k(size_t d, size_t k);

// concatentation
Vector concatenate(const Vector &l, const Vector &r);

// Matrix utilities

// transpose
Matrix transpose(Matrix M);

// slice each Vector of the Matrix and return the result
Matrix slice_matrix(const Matrix &, const std::slice&);
