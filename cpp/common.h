//common.h
#pragma once

#include <iostream>
#include <stdexcept>
#include <valarray>
#include <vector>

using Vector = std::valarray<double>;
using Matrix = std::vector<Vector>;

//global variable used to control reading vector from stdin
extern size_t d;

Matrix transpose(const Matrix &M);
bool check_empty_matrix(const Matrix &M);

std::istream& operator>>(std::istream&, Vector&);
std::istream& operator>>(std::istream&, Matrix&);

std::ostream& operator<<(std::ostream& o, const Vector&);
std::ostream& operator<<(std::ostream& o, const Matrix&);

class input_error : public std::runtime_error {
public:
  input_error(const char*s) : std::runtime_error{s} {}
  input_error(const std::string &s) : std::runtime_error{s} {}
};
