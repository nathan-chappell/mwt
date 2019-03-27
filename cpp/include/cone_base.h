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
class cone_base {
protected:
  math_vectors A; //matrix
  int d;          //dimension
  void clear();

public:
  cone_base() : d{-1} {}
  ~cone_base() { clear(); }

  void read_interactive();
  void read_file(const std::string&);

  //IO
  friend std::ostream &operator<<(std::ostream &, const cone_base&);
  friend void read_in(cone_base&, std::istream &, std::ostream*);
};
