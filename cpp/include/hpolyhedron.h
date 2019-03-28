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

  void read_in(std::istream &, std::ostream *) override;
  std::string to_string() const override;
};
