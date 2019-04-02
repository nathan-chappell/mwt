//hpolyhedron.h
#pragma once

#include "polyhedra_common.h"

/*
 * Ax <= b
 */
class HPolyhedron : public serial_base {
protected:
  constraint_vectors A;
  int d;
  void clear();

public:
  HPolyhedron() { clear(); }
  ~HPolyhedron() override { clear(); }

  const constraint_vectors &get_constraint_vectors() const { return A; }

  //serial_base overrides
  void read_in(std::istream &, std::ostream *) override;
  std::string to_string() const override;
};
