// test_functions.h

#include "linear_algebra.h"

extern int verbosity;

struct cone_test_case {
  std::string name;
  Matrix rep; // vectors for H or V cone
  Matrix key; // minimal genearating set of dual vectors
  Matrix(*transform)(Matrix);

  bool run_test() const;
};

struct hpoly_test_case {
  std::string name;
  Matrix hpoly; // vectors for H-Polyhedron
  VPoly key;    // minimal genearating set of dual vectors

  bool run_test() const;
};

struct vpoly_test_case {
  std::string name;
  VPoly  vpoly; // vectors for V-Polyhedron
  Matrix key;   // minimal genearating set of dual vectors

  bool run_test() const;
};

double operator*(const Vector &l, const Vector &r);
double norm(const Vector &v);

bool is_equal(const Vector &l, const Vector &);
bool has_equal_member(const Matrix &M, const Vector &);

//
// ray-equivalence (exists s >= 0 : l == s*r)
bool is_equivalent(const Vector &l, const Vector &);
bool has_equivalent_member(const Matrix &M, const Vector &);


// each v in generators has an equivalent member in vcone
bool subset_mod_eq(const Matrix &generators, const Matrix &vcone);
bool subset(const Matrix &generators, const Matrix &vcone);

//
// tests ray against constraints (<A_i,ray> <= 0)
bool ray_satisfied(const Vector &constraint,  const Vector &ray);
bool ray_satisfied(const Matrix &constraints, const Vector &ray);
bool rays_satisfied(const Matrix &constraints, const Matrix &rays);

// tests vec against constraints (<A_i,vec> <= b_i)
bool vec_satisfied(const Vector &constraint,  const Vector &vec);
bool vec_satisfied(const Matrix &constraints, const Vector &vec);
bool vecs_satisfied(const Matrix &constraints, const Matrix &vecs);

// all_satisfied(l,r)
// subset_mod_eq(key, r)
bool equivalent_cone_rep(const Matrix &l, const Matrix &r, const Matrix &key);

//TODO test case for polyhedra
