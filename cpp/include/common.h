//common.h
#pragma once

#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <valarray>
#include <vector>

using Vector = std::valarray<double>;
using Matrix = std::vector<Vector>;

struct VPoly {
  Matrix U;
  Matrix V;
};

// global variable used to control reading vector from stdin
// also used in fourier_motzkin
extern size_t d;

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

// Fourier Motzkin Elimination

bool check_empty_matrix(const Matrix &M);
Matrix transpose(const Matrix &M);

// keep only the first d elements of each vector
Matrix project_matrix(const Matrix &M);

// Fourier Motzkin Elimation on index k
Matrix fourier_motzkin(Matrix M, size_t k);
