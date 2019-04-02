//polyhedra_hcone.cc

#include "hcone.h"

HCone::HCone(math_vectors &&mvs) : cone_base{move(mvs)} {}

void push_ID_A(math_vectors &result, const math_vectors &A, double scale) {
  size_t m{A.size()};
  size_t n{A.front().size()};
  for (size_t k = 0; k < n; ++k) {
    result.emplace_back(n+m);
    result.back()[k] = 1. * scale;
    size_t j = 0;
    for (auto &&it = A.begin(); it != A.end(); ++it,++j) {
      result.back()[n+j] = (*it)[j] * scale;
    }
  }
}

void push_ID_M(math_vectors &result, const math_vectors &A) {
  size_t m{A.size()};
  size_t n{A.front().size()};
  for (size_t k = 0; k < m; ++k) {
    result.emplace_back(n+m);
    result.back()[k+n] = 1;
  }
}

/*                    n  n m
 *                   (I -I 0) n
 * {Ax <= 0} -> cone (A -A I) m
 *
 */
math_vectors HCone::lift() const {
  if (A.empty()) return {};
  math_vectors result;
  push_ID_A(result, A, 1);
  push_ID_A(result, A, -1);
  push_ID_M(result, A);
  //lift the thing
  return result;
}
