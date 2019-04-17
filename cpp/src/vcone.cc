//vcone.cc

#include "vcone.h"
#include <stdexcept>

using namespace std;

VCone::VCone(math_vectors &&mvs) : cone_base{move(mvs)} {}

void push_0_nID(math_vectors &mvs, const size_t n, const size_t d) {
  for (size_t row = 0; row < n; ++row) {
    mvs.emplace_back(n+d);
    mvs.back()[d+row] = -1;
  }
}

void push_ID_V(math_vectors &mvs, const math_vectors &A, 
               const size_t n, const size_t d, bool positive) {
  for (size_t row = 0; row < d; ++row) {
    mvs.emplace_back(d+n);
    mvs.back()[row] = positive ? 1 : -1;
    size_t dim = d;
    for_each(A.begin(), A.end(), [&mvs, row, dim, positive] 
      (const math_vector &mv) mutable {
        mvs.back()[dim++] = positive ? mv[row] * -1 : mv[row];
    });
  }
}

/*             d  n
 *           ( 0 -I) n
 *           ( I -V) d
 *cone(V) -> (-I  V) d
 */
math_vectors VCone::lift() const {
  if (A.empty() || !A.front().size()) {
    throw logic_error("lifting empty cone");
  }
  bool POS = true;
  bool NEG = false;
  const size_t n = A.size();
  math_vectors result;
  push_0_nID(result, n, d);
  push_ID_V(result, A, n, d, POS);
  push_ID_V(result, A, n, d, NEG);
  return result;
}
