//lifted_hcone.h
#pragma once

#include "hcone.h"

#include <list>

class LiftedHCone : public HCone { 
  std::list<size_t> lifted_dimensions;
public:
  LiftedHCone(math_vectors &&mvs, size_t);
  std::list<size_t> get_dimensions() const { return lifted_dimensions; }
};
