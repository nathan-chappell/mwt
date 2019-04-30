// test_functions.cpp

#include "test_functions.h"
#include "polyhedra.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

const string dashes = string(8,'-');

int verbosity{0};

void log(const string &m, int verbosity_level) {
  if (verbosity >= verbosity_level) {
    clog << m << endl;
  }
}

// l should be shorter than r
double operator*(const Vector &l, const Vector &r) {
  if (l.size() > r.size()) {
    throw runtime_error{"inner product: l > r"};
  }
  return inner_product(begin(l), end(l), begin(r), 0.);
}

double norm(const Vector &v) {
  return sqrt(v*v);
}

// used to test for equality of vectors modulo some difference...
bool approximately_zero(const Vector &v) {
  const double error = .000001;
  return norm(v) < error;
}

bool is_equivalent(const Vector &l, const Vector &r) {
  if (l.size() != r.size()) return false;
  if (norm(l) == 0 || norm(r) == 0) {
    return norm(l) == 0 && norm(r) == 0;
  }
  return approximately_zero(l / norm(l) - r / norm(r));
}

bool is_equal(const Vector &l, const Vector &r) {
  if (l.size() != r.size()) return false;
  return approximately_zero(l - r);
}

bool has_equivalent_member(const Matrix &M, const Vector &v) {
  if (!any_of(M.begin(), M.end(), 
    [&](const Vector &u) { return is_equivalent(u,v); })) {
    ostringstream oss;
    oss << dashes << " no equivalent member found for:\n" << v << endl;
    log(oss.str(),1);
    return false;
  }
  return true;
}

bool has_equal_member(const Matrix &M, const Vector &v) {
  if (!any_of(M.begin(), M.end(), 
    [&](const Vector &u) { return is_equal(u,v); })) {
    ostringstream oss;
    oss << dashes << " no equal member found for:\n" << v << endl;
    log(oss.str(),1);
    return false;
  }
  return true;
}

// each v in generators has an equivalent member in vcone
bool subset_mod_eq(const Matrix &generators, const Matrix &vcone) {
  return all_of(generators.begin(), generators.end(), 
    [&](const Vector &g) { return has_equivalent_member(vcone, g); });
}

// each v in generators has an equivalent member in vcone
bool subset(const Matrix &generators, const Matrix &vcone) {
  return all_of(generators.begin(), generators.end(), 
    [&](const Vector &g) { return has_equal_member(vcone, g); });
}

//
// tests ray against constraints (<A_i,ray> <= 0)
bool ray_satisfied(const Vector &constraint,  const Vector &ray) {
  if (constraint.size() != ray.size() && constraint.size()-1 != ray.size()) {
    throw runtime_error{"bad ray vs constraint"};
  }
  double ip = ray * constraint;
  if (!(ip <= 0)) { 
    ostringstream oss;
    oss << dashes << " ray not satisfied!\n" << "ray: " << ray << "\nconstraint: "
        << constraint << "\n ray * constraint = " << ip << endl;
    log(oss.str(), 1);
    return false;
  }
  return true; 
}

bool ray_satisfied(const Matrix &constraints, const Vector &ray) {
  return all_of(constraints.begin(), constraints.end(),
    [&](const Vector &cv) { return ray_satisfied(cv, ray); });
}

bool rays_satisfied(const Matrix &constraints, const Matrix &rays) {
  return all_of(rays.begin(), rays.end(), 
    [&](const Vector &ray) { return ray_satisfied(constraints, ray); });
}

// tests vec against constraints (<A_i,vec> <= b_i)
bool vec_satisfied(const Vector &constraint,  const Vector &vec) {
  if (constraint.size()-1 != vec.size()) {
    throw runtime_error{"bad vec vs constraint"};
  }
  double ip = vec * constraint;
  if (!(ip <= constraint[constraint.size()-1])) { 
    ostringstream oss;
    oss << dashes << " vec not satisfied!\n" << "vec: " << vec << "\nconstraint: "
        << constraint << "\n vec * constraint = " << ip << endl;
    log(oss.str(), 1);
    return false;
  }
  return true; 
}

bool vec_satisfied(const Matrix &constraints, const Vector &vec) {
  return all_of(constraints.begin(), constraints.end(),
    [&](const Vector &cv) { return vec_satisfied(cv, vec); });
}

bool vecs_satisfied(const Matrix &constraints, const Matrix &vecs) {
  return all_of(vecs.begin(), vecs.end(),
    [&](const Vector &vec) { return vec_satisfied(constraints, vec); });
}

// all_satisfied(l,r)
// subset_mod_eq(key, r)
bool equivalent_cone_rep(const Matrix &cone, const Matrix &key,
                         const Matrix &alt_rep) {
  return rays_satisfied (cone, alt_rep) && 
         subset_mod_eq  (key, alt_rep);
}

bool equivalent_hpoly_rep(const Matrix &hpoly, const VPoly &key,
                          const VPoly  &vpoly) {
  return rays_satisfied (hpoly, vpoly.U) && 
         vecs_satisfied (hpoly, vpoly.V) && 
         subset_mod_eq  (key.U, vpoly.U) &&
         subset         (key.V, vpoly.V);
}

bool equivalent_vpoly_rep(const VPoly  &vpoly, const Matrix &key,
                          const Matrix &hpoly) {
  return rays_satisfied (hpoly, vpoly.U) && 
         vecs_satisfied (hpoly, vpoly.V) && 
         subset_mod_eq  (key, hpoly);
}

bool cone_test_case::run_test() const {
  auto alt_rep = transform(rep);
  if (!equivalent_cone_rep(rep, key, alt_rep)) {
    log(dashes + " TEST FAILED: " + name, 0);
    ostringstream oss;
    oss << "test: " << rep << "key: " << key << "alt_rep: " << alt_rep;
    log (oss.str(), 2);
    return false;
  }
  return true;
}

bool hpoly_test_case::run_test() const {
  auto vpoly = hpoly_to_vpoly(hpoly);
  if (!equivalent_hpoly_rep(hpoly, key, vpoly)) {
    log(dashes + " TEST FAILED: " + name, 0);
    ostringstream oss;
    oss << "test: " << hpoly << "key: " << key << "vpoly: " << vpoly;
    log (oss.str(), 2);
    return false;
  }
  return true;
}

bool vpoly_test_case::run_test() const {
  auto hpoly = vpoly_to_hpoly(vpoly);
  if (!equivalent_vpoly_rep(vpoly, key, hpoly)) {
    log(dashes + " TEST FAILED: " + name, 0);
    ostringstream oss;
    oss << "test: " << vpoly << "key: " << key << "hpoly: " << hpoly;
    log (oss.str(), 2);
    return false;
  }
  return true;
}
