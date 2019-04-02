// hcone.h
#pragma once

#include "cone_base.h"
#include "polyhedra_common.h"
#include "hpolyhedron.h"

/*
 * Ax <= 0
 */
class HCone : public cone_base {
public:
  HCone(math_vectors &&); //construct base
  HCone() = default;
  math_vectors lift() const;
};
