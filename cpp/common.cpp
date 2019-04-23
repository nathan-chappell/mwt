//common.cpp

#include "common.h"

using namespace std;

std::ostream& operator<<(std::ostream& o, const Vector& v) {
  for (auto &&d : v) {
    o << d << " ";
  }
  return o;
}

std::ostream& operator<<(std::ostream& o, const Matrix& m) {
  o << dimension << endl;
  for (auto &&v : m) {
    o << v << endl;
  }
  return o;
}


