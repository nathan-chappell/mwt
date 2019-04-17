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
  VPolyhedron(math_vectors &&U, math_vectors &&V);

  const math_vectors &get_U() const { return U; }
  const math_vectors &get_V() const { return V; }

  void read_in(std::istream &, std::ostream *) override;
  std::string to_string() const override;
};
