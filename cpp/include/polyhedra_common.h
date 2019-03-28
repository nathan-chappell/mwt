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
template<typename... Ts>
using def_container = std::list<Ts...>;
using math_vectors  = def_container<math_vector>;

// <a,x> <= b
struct constraint_vector {
  math_vector a;
  ordered_field b;
  size_t size() const { return a.size(); }
};

using constraint_vectors = def_container<constraint_vector>;

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

int          read_dimension    (std::istream &is, std::ostream * = nullptr);
math_vector  read_math_vector  (std::istream &is, int d, 
                                std::ostream * = nullptr);
math_vectors read_math_vectors (std::istream &is, int d, 
                                std::ostream * = nullptr, 
                                const std::string& = "");

constraint_vector  read_constraint_vector (std::istream &is, int d,
                                           std::ostream * = nullptr);
constraint_vectors read_constraint_vectors(std::istream &is, int d,
                                           std::ostream * = nullptr);

// parse errors
//
#define FILE_LOCATION std::string{__FILE__ ":"} + std::to_string(__LINE__)
#define READ_ERROR(m) polyhedra_read_error { FILE_LOCATION + " -- " + (m) }

std::string unexpected_char_message(int c);

class polyhedra_read_error : public std::exception {
  std::string message;

public:
  polyhedra_read_error(const std::string &m) : message{m} {}
  const char *what() const noexcept override { return message.c_str(); }
};

// parse errors

// IO
