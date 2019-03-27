// vpolyhedron.h
#pragma once

#include "polyhedra_common.h"

/*
 * cone(U) _+_ conv(V)
 */
class VPolyhedron {
protected:
  math_vectors U, V;
  int d;
  void clear();

public:
  VPolyhedron() { clear(); }
  ~VPolyhedron() { clear(); }
};
