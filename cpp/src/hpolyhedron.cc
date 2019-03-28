//hpolyhedron.cc

#include "hpolyhedron.h"

using namespace std;

void HPolyhedron::read_in(istream &is, ostream *o) {
  clear();
  conditional_log(o,"input hpolyhedron (q or eof to quit)");
  d = read_dimension(is, o);
  A = read_constraint_vectors(is, d, o);
  if (is.eof()) {
    return;
  } else if (is.peek() == 'q') {
    is.get();
    return;
  } else {
    throw READ_ERROR(unexpected_char_message(is.peek()));
  }
}

// hpolyhedron

void HPolyhedron::clear() {
  A.clear();
  d = -1;
}

std::string HPolyhedron::to_string() const {
  ostringstream o;
  o << d << "\n" << A << "\n";
  return o.str();
}
