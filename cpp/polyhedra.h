// polyhedra.h

#include <iostream>
#include <list>
#include <valarray>

using ordered_field = double;
using math_vector   = std::valarray<ordered_field>;
using math_vectors  = std::list<math_vector>;

math_vectors get_math_vector(std::istream &);
math_vectors get_math_vectors(std::istream &);
std::ostream &operator<<(ostream &, const math_vectors &);
std::ostream &operator<<(ostream &, const math_vector &);

/*
 * Ax <= 0
 */
class HCone {
protected:
  math_vectors A;

public:
  HCone(const math_vectors &);
  HCone(math_vectors &&);
  friend std::ostream &operator<<(std::ostream &, const HCone &);
  virtual ~HCone(){};
};

/*
 * Ax <= b
 */
class HPolyhedron : protected HCone {
protected:
  math_vector b;

public:
  HPolyhedron(const math_vectors &, const math_vector &);
  HPolyhedron(math_vectors &&, math_vector &&);
  friend std::ostream &operator<<(std::ostream &, const HPolyhedron &);
};

/*
 * cone(U)
 */
class VCone {
protected:
  math_vectors U;

public:
  VCone(const math_vectors &);
  VCone(math_vectors &&);
  virtual ~VCone(){};
  friend std::ostream &operator<<(std::ostream &, const VCone &);
};

/*
 * cone(U) _+_ conv(V)
 */
class VPolyhedron : protected VCone {
protected:
  math_vectors V;

public:
  VPolyhedron(const math_vectors &, const math_vectors &);
  VPolyhedron(math_vectors &&, math_vectors &&);
  friend std::ostream &operator<<(std::ostream &, const VPolyhedron &);
};
