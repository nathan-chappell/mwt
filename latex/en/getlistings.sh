#!/bin/bash

LISTING=""
CPP_DIR="../../cpp"
CMD_PREFIX="lst"

# $1 range, $2 file
get_listing() {
  lines=( $(eval "sed -n '$1 =' $2") )
  LISTING="\\lstinputlisting[firstline=${lines[0]}, firstnumber=${lines[0]}, lastline=${lines[-1]}]{$2}"
}

# $1 begin, $2 end, $3 file, $4 newcommand name
makecommand() {
  get_listing "$2" "$3"
  echo "\\newcommand{\\${CMD_PREFIX}$1}{$LISTING}"
}

close_brace="^}"
blank_line="^$"

linear_algebra_h="${CPP_DIR}/include/linear_algebra.h"
linear_algebra_cpp="${CPP_DIR}/src/linear_algebra.cpp"
fourier_motzkin_h="${CPP_DIR}/include/fourier_motzkin.h"
fourier_motzkin_cpp="${CPP_DIR}/src/fourier_motzkin.cpp"
polyhedra_h="${CPP_DIR}/include/polyhedra.h"
polyhedra_cpp="${CPP_DIR}/src/polyhedra.cpp"
test_functions_h="${CPP_DIR}/testing/test_functions.h"
test_functions_cpp="${CPP_DIR}/testing/test_functions.cpp"

makecommand "tdVecs"\
             "/using Vector = std::valarray<double>;/,/using Vectors = std::vector<Vector>;/"\
             "$linear_algebra_h"

makecommand "Matrix"\
             "/class Matrix {/,/$close_brace/"\
             "$linear_algebra_h"

makecommand "VPoly"\
             "/struct VPoly {/,/$close_brace/"\
             "$linear_algebra_h"

makecommand "inputerror"\
             "/class input_error : public std::runtime_error {/,/$close_brace/"\
             "$linear_algebra_h"

makecommand "issV"\
             "/std::istream& operator>>(std::istream&, Vector&);/,/std::istream& operator>>(std::istream&, VPoly&);/"\
             "$linear_algebra_h"

makecommand "ossV"\
             "/std::ostream& operator<<(std::ostream& o, const Vector&);/,/std::ostream& operator<<(std::ostream& o, const VPoly&);/"\
             "$linear_algebra_h"

makecommand "usage"\
             "/int usage();/"\
             "$linear_algebra_h"

makecommand "ek"\
             "/Vector e_k(size_t d, size_t k) {/,/$close_brace/"\
             "$linear_algebra_cpp"

makecommand "concatenate"\
             "/Vector concatenate(const Vector &l, const Vector &r) {/,/$close_brace/"\
             "$linear_algebra_cpp"

makecommand "getcolumn"\
             "/Vector get_column(const Matrix &M, size_t k) {/,/$close_brace/"\
             "$linear_algebra_cpp"

makecommand "transpose"\
             "/Matrix transpose(const Matrix &M) {/,/$close_brace/"\
             "$linear_algebra_cpp"

makecommand "slicematrix"\
             "/Matrix slice_matrix(const Matrix &M, const std::slice &s) {/,/$close_brace/"\
             "$linear_algebra_cpp"

#// fourier_motzkin.h 

makecommand "Lift"\
             "/typedef Matrix(\*Lift)(const Matrix&);/"\
             "$fourier_motzkin_h"


#// fourier_motzkin.cpp

makecommand "indexinslice"\
             "/bool index_in_slice(size_t index, const slice &s) {/,/$close_brace/"\
             "$fourier_motzkin_cpp"

makecommand "fouriermotzkin"\
             "/Matrix fourier_motzkin(Matrix M, size_t k) {/,/$close_brace/"\
             "$fourier_motzkin_cpp"

# parts of fourier_motzkin worth explaining
makecommand "FMEPart"\
             "/const auto z_end/,/v\[k\] > 0/"\
             "$fourier_motzkin_cpp"

makecommand "FMEMove"\
            "/move(M.begin(), z_end, back_inserter(result));/"\
             "$fourier_motzkin_cpp"

makecommand "FMEConvolute"\
            "/for (auto p_it = z_end; p_it != p_end; ++p_it)/,/^  }/"\
             "$fourier_motzkin_cpp"

makecommand "slicedfouriermotzkin"\
             "/Matrix sliced_fourier_motzkin(Matrix M, const slice &s) {/,/$close_brace/"\
             "$fourier_motzkin_cpp"

makecommand "generalizedlift"\
             "/Matrix generalized_lift(const Matrix &cone/,/$close_brace/"\
             "$fourier_motzkin_cpp"

makecommand "liftvcone"\
             "/Matrix lift_vcone(const Matrix &vcone) {/,/$close_brace/"\
             "$fourier_motzkin_cpp"

makecommand "lifthcone"\
             "/Matrix lift_hcone(const Matrix &hcone) {/,/$close_brace/"\
             "$fourier_motzkin_cpp"

makecommand "conetransform"\
             "/Matrix cone_transform(const Matrix &cone, Lift lift) {/,/$close_brace/"\
             "$fourier_motzkin_cpp"

makecommand "vconetohcone"\
             "/Matrix vcone_to_hcone(Matrix vcone) {/,/$close_brace/"\
             "$fourier_motzkin_cpp"

makecommand "hconetovcone"\
             "/Matrix hcone_to_vcone(Matrix hcone) {/,/$close_brace/"\
             "$fourier_motzkin_cpp"


#//polyhedra.cpp

makecommand "hpolytohcone"\
             "/Matrix hpoly_to_hcone(Matrix hpoly) {/,/$close_brace/"\
             "$polyhedra_cpp"

makecommand "hconetohpoly"\
             "/Matrix hcone_to_hpoly(Matrix hcone) {/,/$close_brace/"\
             "$polyhedra_cpp"

makecommand "vpolytovcone"\
             "/Matrix vpoly_to_vcone(VPoly vpoly) {/,/$close_brace/"\
             "$polyhedra_cpp"

makecommand "normalizedP"\
             "/Matrix normalized_P(const Matrix &U) {/,/$close_brace/"\
             "$polyhedra_cpp"

makecommand "vconetovpoly"\
             "/VPoly vcone_to_vpoly(Matrix vcone) {/,/$close_brace/"\
             "$polyhedra_cpp"

makecommand "hpolytovpoly"\
             "/VPoly hpoly_to_vpoly(Matrix hpoly) {/,/$close_brace/"\
             "$polyhedra_cpp"

makecommand "vpolytohpoly"\
             "/Matrix vpoly_to_hpoly(VPoly vpoly) {/,/$close_brace/"\
             "$polyhedra_cpp"



#// test_functions.h

makecommand "hconetestcasea"\
             "/struct hcone_test_case {/,/$close_brace/"\
             "$test_functions_h"

makecommand "vconetestcasea"\
             "/struct vcone_test_case {/,/$close_brace/"\
             "$test_functions_h"

makecommand "hpolytestcaseb"\
             "/struct hpoly_test_case {/,/$close_brace/"\
             "$test_functions_h"

makecommand "vpolytestcaseb"\
             "/struct vpoly_test_case {/,/$close_brace/"\
             "$test_functions_h"



#// test_functions.cpp

makecommand "operator"\
             "/double operator\*(const Vector &l, const Vector &r) {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "norm"\
             "/double norm(const Vector &v) {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "approximatelyzeroa"\
             "/bool approximately_zero(double d) {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "approximatelyltzero"\
             "/bool approximately_lt_zero(double d) {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "approximatelyzerob"\
             "/bool approximately_zero(const Vector &v) {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "isequivalent"\
             "/bool is_equivalent(const Vector &l, const Vector &r) {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "isequal"\
             "/bool is_equal(const Vector &l, const Vector &r) {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "hasequivalentmember"\
             "/bool has_equivalent_member(const Matrix &M/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "hasequalmember"\
             "/bool has_equal_member(const Matrix &M, const Vector &v) {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "subsetmodeq"\
             "/bool subset_mod_eq(const Matrix &generators/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "subset"\
             "/bool subset(const Matrix &generators/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "raysatisfieda"\
             "/bool ray_satisfied(const Vector &constraint,/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "raysatisfiedb"\
             "/bool ray_satisfied(const Matrix &constraints,/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "rayssatisfied"\
             "/bool rays_satisfied(const Matrix &constraints,/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "vecsatisfieda"\
             "/bool vec_satisfied(const Vector &constraint,/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "vecsatisfiedb"\
             "/bool vec_satisfied(const Matrix &constraints,/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "vecssatisfied"\
             "/bool vecs_satisfied(const Matrix &constraints,/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "equivalentconerep"\
             "/bool equivalent_cone_rep(const Matrix &cone,/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "equivalenthpolyrep"\
             "/bool equivalent_hpoly_rep(const Matrix &hpoly,/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "equivalentvpolyrep"\
             "/bool equivalent_vpoly_rep(const VPoly  &vpoly,/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "hconetestcaseb"\
             "/bool hcone_test_case::run_test() const {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "vconetestcaseb"\
             "/bool vcone_test_case::run_test() const {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "hpolytestcasea"\
             "/bool hpoly_test_case::run_test() const {/,/$close_brace/"\
             "$test_functions_cpp"

makecommand "vpolytestcasea"\
             "/bool vpoly_test_case::run_test() const {/,/$close_brace/"\
             "$test_functions_cpp"
