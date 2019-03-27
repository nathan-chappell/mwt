// cone_base.cc

#include "cone_base.h"

#include <fstream>
#include <iomanip>

using namespace std;

#define FILE_LOCATION string{__FILE__ ":"} + to_string(__LINE__)

namespace {
int fmt_width{6};
}; // namespace

math_vector read_vector(istream &is, int d) {
  math_vector v(d);
  for (int i = 0; i < d; ++i) {
    cin >> v[i];
  }
  return v;
}

void read_in(cone_base &cone, istream &is, ostream *o = nullptr) {
  cone.clear();
  if (o) {
    *o << "enter dimension: ";
  }
  is >> cone.d;
  if (cone.d < 0) {
    throw polyhedra_read_error{FILE_LOCATION + "dimension < 0"};
  }
  while (is) {
    if (o) {
      *o << "\nenter row (enter q to quit): ";
    }
    if (!(is >> ws) || is.peek() == 'q') {
      // if it is a q, then eat it
      if (is) {
        is.get();
      }
      break;
    } else {
      auto &&v = read_vector(is, cone.d);
      if (static_cast<int>(v.size()) != cone.d) {
        throw polyhedra_read_error{FILE_LOCATION + "wrong dimension!"};
      }
      cone.A.push_back(move(v));
    }
  }
}

// cone_base

void cone_base::clear() {
  A.clear();
  d = -1;
}

void cone_base::read_interactive() { read_in(*this, cin, &cout); }

void cone_base::read_file(const string &filename) {
  ifstream file{filename};
  read_in(*this, file);
}

std::ostream &operator<<(std::ostream &o, const cone_base &cone) {
  for (auto &&v : cone.A) {
    for (auto &&val : v) {
      o << setw(fmt_width) << val;
    }
    o << endl;
  }
  return o;
}
