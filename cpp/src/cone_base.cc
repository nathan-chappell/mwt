// cone_base.cc

#include "cone_base.h"

#include <fstream>
#include <iomanip>

using namespace std;

void cone_base::read_in(istream &is, ostream *o) {
  clear();
  conditional_log(o,"input cone (q or eof to quit)");
  d = read_dimension(is, o);
  conditional_log(o,"read d:"s + ::to_string(d));
  A = read_math_vectors(is, d, o);
  if (is.eof()) {
    return;
  } else if (is.peek() == 'q') {
    is.get();
    return;
  } else {
    throw READ_ERROR("reading unexpectedly stopped with: "s + 
                     static_cast<char>(is.peek()) +
                     "(maybe invalid character?)"s);
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
