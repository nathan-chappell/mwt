// vpolyhedron.h
#pragma once

#include "polyhedra_common.h"

/*
 * cone(U) _+_ conv(V)
 */
class VPolyhedron : public serial_base {
protected:
  math_vectors U, V;
  int d;
  void clear();

public:
  VPolyhedron() { clear(); }
  ~VPolyhedron() override { clear(); }
  VPolyhedron(math_vectors &&U, math_vectors &&V) : U{move(U)}, V{move(V)} {}

  void read_in(std::istream &, std::ostream *) override;
  std::string to_string() const override;
};
