//polyhedra_hcone.cc

#include "hcone.h"

HCone::HCone(math_vectors &&mvs) : cone_base{move(mvs)} {}

/* 
 * (e_j)
 * (A^j)
 */
math_vector get_ej_Aj(const math_vectors &A, const size_t &j, bool positive) {
  const size_t m{A.size()};
  const size_t n{A.front().size()};
  math_vector result(m + n);
  result[j] = 1;
  size_t row{0};
  for (auto &&col : A) {
    result[n+row++] = col[j];
  }
  if (!positive) {
    result *= -1;
  }
  return result;
}

void push_ID_A(math_vectors &result, const math_vectors &A) {
  bool POS = true, NEG = false;
  size_t n{A.front().size()};
  for (size_t j = 0; j < n; ++j) {
    result.push_back(get_ej_Aj(A,j,POS));
  }
  for (size_t j = 0; j < n; ++j) {
    result.push_back(get_ej_Aj(A,j,NEG));
  }
}

void push_0_ID(math_vectors &result, const math_vectors &A) {
  const size_t &m{A.size()};
  const size_t &n{A.front().size()};
  for (size_t k = 0; k < m; ++k) {
    result.emplace_back(n+m);
    result.back()[k+n] = 1;
  }
}

/*                    n  n m
 *                   (I -I 0) n
 * {Ax <= 0} -> cone (A -A I) m
 */
math_vectors HCone::lift() const {
  if (A.empty()) return {};
  math_vectors result;
  push_ID_A(result, A);
  push_0_ID(result, A);
  return result;
}
