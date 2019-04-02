//cone_base.h
#pragma once

#include "polyhedra_common.h"

/*
 * A base class for cones.  hcones and vcones have precisely the same
 * implementation as of right now, so they just declare a new type and directly
 * inherit this guy.  The destructor is not virtual because I don't intend to
 * use the class hierarchy in this way.  The only forseen divergence in
 * implementation is for IO, but I'll cross that bridge when I get to it.
 */
class cone_base : public serial_base {
protected:
  math_vectors A; //matrix
  int d;          //dimension
  void clear();
public:
  cone_base() : d{-1} {}
  ~cone_base() override { clear(); }
  cone_base(math_vectors &&);
  const math_vectors &get_math_vectors() const { return A; }
  //serial_base overrides
  void read_in(std::istream &, std::ostream*) override;
  std::string to_string() const override;
};

