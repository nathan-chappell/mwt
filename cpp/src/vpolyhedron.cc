//vpolyhedron.cc

#include "vpolyhedron.h"

using namespace std;

//
const string &continue_message{"(V to start entering vertices)"};

VPolyhedron::VPolyhedron(math_vectors &&U, math_vectors &&V) 
  : U{move(U)}, V{move(V)}, d{-1} {
  //check to make sure U and V are compatible...
  if (!U.empty() && !V.empty() && U.front().size() != V.front().size()) {
    throw polyhedra_read_error{"U and V not compatible"};
  } else if (!U.empty()) {
    d = U.front().size();
  } else if (!V.empty()) {
    d = V.front().size();
  }
}

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
