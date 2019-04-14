// mwt.cc

#include "mwt.h"

#include <iostream>

using namespace std;

//TODO V -> H
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
  clog << hpolyhedron << endl;
  //converting constructor...
	return relax_constraints(hpolyhedron.get_constraint_vectors());;
}
LiftedHCone lift     (const HCone &hcone) {
	clog << "lifting HCone" << endl;
  clog << hcone << endl;
  //TODO Cone Lift is all fucked up.  Not moving A^j to higher dimensions
	return {hcone.lift(), hcone.get_math_vectors().front().size()};
}
VCone       drop     (const LiftedHCone &liftedhcone) {
	clog << "dropping LiftedHCone" << endl;
  clog << liftedhcone.get_math_vectors() << endl;
  clog << "pi: ";
  for (auto &&i : liftedhcone.get_dimensions()) {
    clog << i << ", ";
  }
  clog << endl;
	return fjoin(liftedhcone.get_math_vectors(), liftedhcone.get_dimensions());
}
VPolyhedron restrict (const VCone &vcone) {
	clog << "restricting VCone" << endl;
  clog << vcone << endl;
	return {project_K(fjoin_k(vcone.get_math_vectors(), 0),{0}),
          project_K(normalize_k(vcone.get_math_vectors(), 0),{0})};
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
  result[0] = -1*cv.b;
  copy(begin(cv.a), end(cv.a), next(begin(result)));
  return result;
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
