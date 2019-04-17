// mwt.cc

#include "mwt.h"

#include <iostream>

using namespace std;

//Generics
VCone       relax    (const VPolyhedron &vpolyhedron) {
	clog << "relaxing VPolyhedron" << endl;
  math_vectors UV;
  transform(vpolyhedron.get_U().cbegin(), vpolyhedron.get_U().cend(), 
    back_inserter(UV), [](const math_vector &mv) { 
      return prepend_value(mv, 0); });
  transform(vpolyhedron.get_V().cbegin(), vpolyhedron.get_V().cend(), 
    back_inserter(UV), [](const math_vector &mv) { 
      return prepend_value(mv, 1); });
	return {move(UV)};
}
LiftedVCone lift     (const VCone &vcone) {
	clog << "lifting VCone" << endl;
  clog << vcone << endl;
	return LiftedVCone{vcone.lift(), vcone.get_d()};
}
HCone       drop     (const LiftedVCone &liftedvcone) {
	clog << "dropping LiftedVCone" << endl;
  clog << "dim: ";
  for (auto &&d : liftedvcone.get_dimensions()) clog << d << ", ";
  clog << endl;
  clog << liftedvcone.get_math_vectors();
	return fjoin(liftedvcone.get_math_vectors(), liftedvcone.get_dimensions());
}
HPolyhedron restrict (const HCone &hcone) {
	clog << "restricting HCone" << endl;
  clog << hcone << endl;
	return reconstrain(hcone.get_math_vectors());
}

HCone       relax    (const HPolyhedron &hpolyhedron) {
	clog << "relaxing HPolyhedron" << endl;
  //clog << hpolyhedron << endl;
  //converting constructor...
	return relax_constraints(hpolyhedron.get_constraint_vectors());;
}
LiftedHCone lift     (const HCone &hcone) {
	clog << "lifting HCone" << endl;
  //clog << hcone << endl;
	return {hcone.lift(), hcone.get_d()};
}
VCone       drop     (const LiftedHCone &liftedhcone) {
	clog << "dropping LiftedHCone" << endl;
	return fjoin(liftedhcone.get_math_vectors(), liftedhcone.get_dimensions());
}
VPolyhedron restrict (const VCone &vcone) {
	clog << "restricting VCone" << endl;
  //clog << vcone << endl;
	return {project_K(fjoin_k(vcone.get_math_vectors(), 0),{0}),
          project_K(normalize_k(vcone.get_math_vectors(), 0),{0})};
}
//Generics

//lifted types
LiftedCone::LiftedCone(math_vectors &&mvs, size_t d) : cone_base{move(mvs)} {
  for (; d < A.front().size(); ++d) {
    lifted_dimensions.push_back(d);
  }
}

LiftedHCone::LiftedHCone(math_vectors &&mvs, size_t d) 
  : LiftedCone{move(mvs), d} {}

LiftedVCone::LiftedVCone(math_vectors &&mvs, size_t d) 
  : LiftedCone{move(mvs), d} {}

//lifted types

//vector operations

math_vector relax_constraint(const constraint_vector &cv) {
  return prepend_value(cv.a,-1*cv.b);
}

math_vectors relax_constraints(const constraint_vectors &cvs) {
  math_vectors result;
  cerr << "relaxing: \n" << cvs << endl;
  for (auto &&cv : cvs) {
    result.push_back(relax_constraint(cv));
  }
  cerr << "result: \n" << result << endl;
  return result;
}

math_vectors normalize_k (math_vectors mvs, const size_t &k) {
  auto p_end = partition(mvs.begin(), mvs.end(),
      [k](const math_vector &v) { return v[k] > 0; });
  math_vectors result;
  transform(mvs.begin(), p_end, back_inserter(result),
      [k](const math_vector &v) { return v[k] == 1 ? v : v/v[k]; });
  return result;
}

math_vector prepend_value(const math_vector &mv, math_vector::value_type v) {
  math_vector result(mv.size()+1);
  result[0] = v;
  copy(begin(mv), end(mv), next(begin(result)));
  return result;
}

constraint_vector reconstrain(const math_vector &mv) {
  constraint_vector cv;
  cv.a.resize(mv.size()-1);
  cv.b = -1*mv[0];
  copy(next(begin(mv)), end(mv), begin(cv.a));
  return cv;
}

constraint_vectors reconstrain(const math_vectors &mvs) {
  constraint_vectors result;
  transform(mvs.begin(), mvs.end(), back_inserter(result), 
    [](const math_vector &mv) { return reconstrain(mv); });
  return result;
}
