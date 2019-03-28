// cone_base.cc

#include "cone_base.h"

using namespace std;

void cone_base::read_in(istream &is, ostream *o) {
  clear();
  conditional_log(o,"input cone (q or eof to quit)");
  d = read_dimension(is, o);
  A = read_math_vectors(is, d, o);
  if (is.eof()) {
    return;
  } else if (is.peek() == 'q') {
    is.get();
    return;
  } else {
    throw READ_ERROR(unexpected_char_message(is.peek()));
  }
}

// cone_base

void cone_base::clear() {
  A.clear();
  d = -1;
}

std::string cone_base::to_string() const {
  ostringstream o;
  o << d << "\n" << A << "\n";
  return o.str();
}
