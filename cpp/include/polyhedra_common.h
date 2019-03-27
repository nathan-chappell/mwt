// polyhedra_common.h
#pragma once

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <valarray>

// basic structures
//
using ordered_field = double;
using math_vector   = std::valarray<ordered_field>;
using math_vectors  = std::list<math_vector>;

// <a,x> <= b
struct constraint_vector {
  math_vector a;
  ordered_field b;
};

using constraint_vectors = std::list<constraint_vector>;

/*
 * Abstract base provided for basic "parsing" or "reading" interface.  Important
 * for testing.
 */
class serial_base {
public:
//main interface
  virtual void        read_in(std::istream &, std::ostream * = nullptr) = 0;
  virtual std::string to_string() const = 0;
  virtual             ~serial_base() {}
//convenience functions
  void read_interactive() { read_in(std::cin, &std::cout); }
  void read_file(const std::string &fname) {
    std::ifstream file{fname};
    read_in(file);
  }
//sends to_string() to ostream
  friend std::ostream &operator<<(std::ostream &, const serial_base &);
};

// basic structures

// IO

//sends message to ostream if not nullptr
void conditional_log(std::ostream *, const std::string &);

std::ostream &operator<<(std::ostream &, const math_vector &);
std::ostream &operator<<(std::ostream &, const math_vectors &);
std::ostream &operator<<(std::ostream &, const constraint_vector &);
std::ostream &operator<<(std::ostream &, const constraint_vectors &);

int               read_dimension        (std::istream &is, 
                                         std::ostream *o);
math_vector       read_math_vector      (std::istream &is, int d, 
                                         std::ostream *);
constraint_vector read_constraint_vector(std::istream &is, int d,
                                         std::ostream *);
math_vectors      read_math_vectors     (std::istream &is, int d, 
                                         std::ostream *o);

// parse errors
//
#define FILE_LOCATION string{__FILE__ ":"} + ::to_string(__LINE__)
#define READ_ERROR(m)                                                          \
  polyhedra_read_error { FILE_LOCATION + " -- " + (m) }

class polyhedra_read_error : public std::exception {
  std::string message;

public:
  polyhedra_read_error(const std::string &m) : message{m} {}
  const char *what() const noexcept override { return message.c_str(); }
};

// parse errors

// IO
