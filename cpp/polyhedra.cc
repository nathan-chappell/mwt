// polyhedra.cc

#include "polyhedra.h"
using namespace std;

math_vectors get_math_vectors(std::istream &i) {
  math_vectors result;
  string line;
  while (getline(i, line)) {
    result.
  }
}
std::ostream &operator<<(ostream &o, const math_vectors &vs) {}
std::ostream &operator<<(ostream &o, const math_vector &v) {}

/*
 * Ax <= 0
 */
// HCone

HCone::HCone(const math_vectors &A) : A{A} {}
HCone::HCone(math_vectors &&) : A{move(A)} {}

std::ostream &operator<<(ostream &o, const HCone &) {}

/*
 * Ax <= b
 */
// HPolyhedron

HPolyhedron::HPolyhedron(const math_vectors &A, const math_vector &b)
    : HCone{A}, b{b} {}
HPolyhedron::HPolyhedron(math_vectors &&A, math_vector &&b) HCone{move(A)},
    b{move(b)} {}

std::ostream &operator<<(ostream &o, const HPolyhedron &) {}

/*
 * cone(U)
 */
// VCone
VCone::VCone(const math_vectors &U) : U{U} {}
VCone::VCone(math_vectors &&U) : U{move(U)} {}

std::ostream &operator<<(ostream &o, const VCone &) {}

/*
 * cone(U) _+_ conv(V)
 */
// VPolyhedron
VPolyhedron::VPolyhedron(const math_vectors &U, const math_vectors &V) 
  : VCone{U}, V{V} {}
VPolyhedron::VPolyhedron(math_vectors &&U, math_vectors &&V) 
  : VCone{move(U)}, V{move(V)} {}

std::ostream &operator<<(ostream &o, const VPolyhedron &) {}
