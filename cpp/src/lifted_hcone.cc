//lifted_hcone.cc

#include "lifted_hcone.h"

#include <numeric>

using namespace std;

LiftedHCone::LiftedHCone(math_vectors &&mvs, size_t d) : HCone(move(mvs)) {
  for (; d < A.front().size(); ++d) {
    lifted_dimensions.push_back(d);
  }
}
