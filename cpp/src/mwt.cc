// mwt.cc

#include "mwt.h"

#include <iostream>

using namespace std;

//Generics
VCone       relax    (const VPolyhedron &vpolyhedron) {
	clog << "relaxing VPolyhedron" << endl;
	return VCone{};
}
LiftedVCone lift     (const VCone &vcone) {
	clog << "lifting VCone" << endl;
	return LiftedVCone{};
}
HCone       drop     (const LiftedVCone &liftedvcone) {
	clog << "dropping LiftedVCone" << endl;
	return HCone{};
}
HPolyhedron restrict (const HCone &hcone) {
	clog << "restricting HCone" << endl;
	return HPolyhedron{};
}

HCone       relax    (const HPolyhedron &hpolyhedron) {
	clog << "relaxing HPolyhedron" << endl;
  //converting constructor...
	return relax_constraints(hpolyhedron.get_constraint_vectors());;
}
LiftedHCone lift     (const HCone &hcone) {
	clog << "lifting HCone" << endl;
	return {hcone.lift(), hcone.get_math_vectors().front().size()};
}
VCone       drop     (const LiftedHCone &liftedhcone) {
	clog << "dropping LiftedHCone" << endl;
	return fjoin(liftedhcone.get_math_vectors(), liftedhcone.get_dimensions());
}
VPolyhedron restrict (const VCone &vcone) {
	clog << "restricting VCone" << endl;
	return {fjoin_k(vcone.get_math_vectors(), 0),
          normalize_k(vcone.get_math_vectors(), 0)};
}
//Generics

//lifted types
LiftedHCone::LiftedHCone(math_vectors &&mvs, size_t d) : HCone(move(mvs)) {
  for (; d < A.front().size(); ++d) {
    lifted_dimensions.push_back(d);
  }
}
//lifted types

//vector operations

math_vector relax_constraint(const constraint_vector &cv) {
  math_vector result(cv.size()+1);
  result[0] = cv.b;
  copy(next(begin(cv.a)), end(cv.a), next(begin(result)));
  return result;
}

math_vectors relax_constraints(const constraint_vectors &cvs) {
  math_vectors result;
  for (auto &&cv : cvs) {
    result.push_back(relax_constraint(cv));
  }
  return result;
}

//K must be sorted
math_vector project_K_v (const math_vector &mv, const std::vector<size_t> &K) {
  math_vector result(mv.size() - K.size());
  size_t k{};
  auto k_it = K.begin();
  for (size_t i = 0; i < mv.size(); ++i) {
    if (*k_it == i) {
      ++k_it;
      continue;
    } else {
      result[k++] = mv[i];
    }
  }
  return result;
}

math_vectors project_K (const math_vectors &mvs, std::vector<size_t> K) {
  math_vectors result;
  sort(K.begin(),K.end());
  for (auto &&mv : mvs) {
    result.push_back(project_K_v(mv,K));
  }
  return result;
}

/*
 * This version projects while doing the join, easier to wait until end
math_vector fjoink_v(const math_vector &p, const math_vector &n, size_t k) {
  math_vector result(p.size() - 1);
  for (size_t i = 0; i < k; ++i) {
    result[i] = -1*n[k]*p[i] + p[k]*n[i];
  }
  for (size_t i = k+1; i < p.size()-1; ++i) {
    result[i] = -1*n[k]*p[i] + p[k]*n[i];
  }
  return result;
}
*/

math_vector fjoink_v(const math_vector &p, const math_vector &n, size_t k) {
  return p[k]*n - n[k]*p;
}

/*
 * not sure whether to take argument by reference or value here...
 * perhaps an ''index set'' would be better than the actual vectors...
 * ...As of right now, projecting is
 * TODO handle case where P or N is empty...
 */
math_vectors fjoin_k (math_vectors mvs, const size_t &k) {
  cerr << "fjoin_k(" << k << "), mvs: \n" << mvs << endl;
  auto z_end = partition(mvs.begin(), mvs.end(), 
                [k](const decltype(mvs)::value_type &mv) { 
                  return mv[k] == 0; });
  auto p_end = partition(z_end, mvs.end(),
                [k](const decltype(mvs)::value_type &mv) { 
                  return mv[k] > 0; });
  /*
   * mvs.begin() -> z_end     ... mv[k] == 0
   * z_end       -> p_end     ... mv[k] < 0
   * p_end       -> mvs.end() ... mv[k] > 0
   */
  {
    auto it = mvs.begin();
    cerr << "Z" << endl;
    for (;it != z_end; ++it) { cerr << *it << endl; }
    cerr << "P" << endl;
    for (;it != p_end; ++it) { cerr << *it << endl; }
    cerr << "N" << endl;
    for (;it != mvs.end(); ++it) { cerr << *it << endl; }
  }
  math_vectors result;
  /*
   * projections wait until end
  transform(mvs.begin(), z_end, back_inserter(result),
      [k](const math_vectors::value_type &mv) { return project_k(mv, k); });
  */
  for (auto it = mvs.begin(); it != z_end; ++it) {
    result.push_back(move(*it)); //gotta be a better way
  }
  for (auto it = z_end; it != p_end; ++it) {
    transform(p_end, mvs.end(), back_inserter(result),
      [k,it](const math_vectors::value_type &mv) {
        return fjoink_v(*it, mv, k);
      });
  }
  cerr << "fjoin_k, result: \n" << result << endl;
  return result;
}

/*
 * should we project throughout or wait until the end?
 * ... easier to wait until the end (dimensions less complicated...)
 */
math_vectors fjoin(math_vectors mvs, const vector<size_t> &dimensions) {
  for (auto d : dimensions) {
    mvs = fjoin_k(mvs, d); 
    cerr << "mvs: \n" << mvs << "\n------------------" << endl;
  }
  return project_K(mvs, dimensions);
}

math_vectors normalize_k (math_vectors mvs, const size_t &k) {
  auto p_end = partition(mvs.begin(), mvs.end(),
      [k](const decltype(mvs)::value_type &v) { return v[k] > 0; });
  math_vectors result;
  transform(mvs.begin(), p_end, back_inserter(result),
      [k](const decltype(mvs)::value_type &v) { return v*(1/v[k]); });
  return result;
}
