//vpolyhedron.cc

#include "vpolyhedron.h"

using namespace std;

//
const string &continue_message{"(V to start entering vertices)"};

void VPolyhedron::clear() {
  U.clear();
  V.clear();
  d = -1;
}

void VPolyhedron::read_in(std::istream &is, std::ostream *o) {
  clear();
  conditional_log(o,"input vpolyhedron (q or eof to quit)");
  d = read_dimension(is, o);
  conditional_log(o,"enter rays " + continue_message);
  U = read_math_vectors(is, d, o, continue_message);
  if (is.peek() == 'V') {
    is.get();
    V = read_math_vectors(is, d, o);
  }
  if (is.eof()) {
    return;
  } else if (is.peek() == 'q') {
    is.get();
    return;
  } else {
    throw READ_ERROR(unexpected_char_message(is.peek()));
  }
}

string VPolyhedron::to_string() const {
  ostringstream o;
  o << d << "\n" << U << "V\n" << V << "\n";
  return o.str();
}
