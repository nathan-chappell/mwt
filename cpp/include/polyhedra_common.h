//polyhedra_common.h
#pragma once

#include <iostream>
#include <list>
#include <valarray>
#include <exception>

using ordered_field = double;
using math_vector   = std::valarray<ordered_field>;
using math_vectors  = std::list<math_vector>;

class polyhedra_read_error : public std::exception {
  std::string message;
  public:
  polyhedra_read_error(const std::string &m) : message{m} {}
  const char* what() const noexcept override { return message.c_str(); }
};


