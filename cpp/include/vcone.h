//vcone.h
#pragma once

#include "polyhedra_common.h"
#include "cone_base.h"

/*
 * cone(A)
 */
class VCone : public cone_base {
public:
  VCone(math_vectors &&); //construct base
  VCone() = default;
};
