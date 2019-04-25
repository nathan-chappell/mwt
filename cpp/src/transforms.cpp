// transforms.cpp

#include "transforms.h"
#include "hcone.h"
#include "vcone.h"
#include "poly_to_cone.h"

using namespace std;

// fourier motzkin for cones

Matrix hcone_to_vcone(Matrix hcone) {
  if (check_empty_matrix(hcone)) {
    throw logic_error{"empty hcone"};
  }
  Matrix result;
  m = hcone.size();
  return HCone::intersect_vcone(HCone::lift_hcone(hcone));
}

Matrix vcone_to_hcone(Matrix vcone) {
  if (check_empty_matrix(vcone)) {
    throw logic_error{"empty vcone"};
  }
  p = vcone.size();
  return VCone::project_hcone(VCone::lift_vcone(vcone));
}

// fourier motzkin for polyhedra
VPoly  hpoly_to_vpoly (Matrix hpoly) {
  return vcone_to_vpoly(hcone_to_vcone(hpoly_to_hcone(move(hpoly))));
}

Matrix vpoly_to_hpoly (VPoly vpoly) {
  return hcone_to_hpoly(vcone_to_hcone(vpoly_to_vcone(move(vpoly))));
}
