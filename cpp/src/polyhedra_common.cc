//polyhedra_common.cc

#include "polyhedra_common.h"
#include <istream>

using namespace std;

//IO

int fmt_width{3};
const string float_begin{"+-.0123456789"};

namespace error_message {
  const string read_dimension{"invalid dimension"};
  const string read_math_vector{"failed to read math_vector" 
                                "(possibly wrong number of elements?)"};
  const string read_constraint_vector_comp{
          "only '<=' comparison is currently supported"};
  const string read_constraint_vector_fail{
          "failed to read constraint_vector (istream fail)"};
  const string read_vectors_dimension{"dimension < 0 (possibly unset)"};
  const string read_vectors_size{"wrong dimension! (or improper cast...)"};
}; //error_message

void conditional_log(ostream *o, const string &m) {
  if (o) {
    *o << m << endl;
  }
}

int read_dimension(istream &is, ostream *o) {
  int d{-1};
  conditional_log(o, "enter dimension: ");
  is >> d;
  if (d < 0 || is.fail()) {
    throw READ_ERROR(error_message::read_dimension);
  }
  return d;
}

math_vector read_math_vector(istream &is, int d, ostream *o) {
  conditional_log(o, "enter math_vector: ");
  math_vector v(d);
  for (auto &e : v) {
    is >> e;
  }
  if (is.fail()) {
    throw READ_ERROR(error_message::read_math_vector);
  }
  cerr << "mv read: " << v << endl;
  return v;
}

constraint_vector read_constraint_vector(istream &is, int d, 
                                         ostream *o) {
  string comparison;
  constraint_vector cv{read_math_vector(is, d, o)};
  conditional_log(o, "enter comparison operator (<=): ");
  is >> ws >> comparison;
  if (comparison != "<=") {
    throw READ_ERROR(error_message::read_constraint_vector_comp);
  } else {
    conditional_log(o, "enter constraint value: ");
    is >> cv.b;
  }
  if (is.fail()) {
    throw READ_ERROR(error_message::read_constraint_vector_fail);
  }
  return cv;
}

/*
 * Generic algorithm for reading many vectors
 */
template <typename R, typename T, typename... Ts>
R read_vectors(T(*read_v)(istream&,int,ostream*), 
                  istream &is, int d, ostream *o,
                  const string &continue_message = "") {
  R result;
  if (d < 0) {
    throw READ_ERROR(error_message::read_vectors_dimension);
  }
  while (is) {
    conditional_log(o, "q or eof to quit | " + continue_message);
    is >> ws;
    if (!is || is.peek() == 'q') {
      return result;
    } else if (float_begin.find(is.peek()) == float_begin.npos) {
      break;
    }
    result.push_back(read_v(is,d,o));
    if (result.back().size() != static_cast<size_t>(d)) {
      throw READ_ERROR(error_message::read_vectors_size);
    }
  }
  return result;
}

math_vectors read_math_vectors(istream &is, int d,
                               ostream *o, 
                               const string &continue_message) {
  return read_vectors<math_vectors>(&read_math_vector, is, d, o, 
                                    continue_message);
}

constraint_vectors read_constraint_vectors(istream &is, int d,
                                           ostream *o) {
  return read_vectors<constraint_vectors>(&read_constraint_vector, is, d, o);
}

ostream &operator<<(ostream &o, const math_vector &v) {
  for (auto &&val : v) {
    o << setw(fmt_width) << right << val << ' ';
  }
  return o;
}

ostream &operator<<(ostream &o, const math_vectors &vs) {
  for (auto &&v : vs) {
    o << v << "\n";
  }
  return o;
}

ostream &operator<<(ostream &o, const constraint_vector &cv) {
  return o << cv.a << " <= " << cv.b;
}

ostream &operator<<(ostream &o, const constraint_vectors &cvs) {
  for (auto &&cv : cvs) {
    o << cv << "\n";
  }
  return o;
}

ostream &operator<<(ostream &o, const serial_base &base) {
  return o << base.to_string();
}

std::string unexpected_char_message(int c) {
  return "reading unexpectedly stopped with: "s + 
            static_cast<char>(c) + 
            "(maybe invalid character?)"s;
}
