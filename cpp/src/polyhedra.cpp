//polyhedra.cpp

#include "polyhedra.h"
#include "hcone.h"
#include "vcone.h"

#include <algorithm>

using namespace std;

// valarray::cshift circularly shifts elements left...

// HP -> HC
// A|b -> -b|A
Matrix hpoly_to_hcone(Matrix hpoly) {
  transform(hpoly.begin(), hpoly.end(), hpoly.begin(),
      [](Vector v) { 
        v[v.size()-1] *= -1;
        return v.cshift(-1); 
      });
  return hpoly;
}

// HC -> HP
// -b|A -> A|b 
Matrix hcone_to_hpoly(Matrix hcone) {
  transform(hcone.begin(), hcone.end(), hcone.begin(),
      [](Vector v) { 
        v[0] *= -1;
        return v.cshift(1); 
      });
  return hcone;
}

// VP -> VC
// U -> |0 1|
//      |U V|
Matrix vpoly_to_vcone(VPoly vpoly) {
  //requires increase in dimension
  Matrix result{vpoly.d+1};
  for (auto &&v : vpoly.U) {
    result.push_back(concatenate({0},v));
  }
  for (auto &&v : vpoly.V) {
    result.push_back(concatenate({1},v));
  }
  return result;
}

//  ?    1
//  U -> V
Matrix normalized_P(Matrix M) {
  if (M.d <= 1) {
    throw std::logic_error{"can't normalize M!"};
  }
  std::slice s{1,d,1};
  Matrix result{s.size()}; // s.size() == d-1
  for (auto &&v : M) {
    // select the vectors with positive 0-th coordinate
    if (v[0] > 0) {
      // normalize the selected vectors,
      result.push_back(v[0] == 1 ? v[s] : v[s] /= v[0]);
    }
  }
  return result;
}

// U -> {Z \cup P*N, P'}
// V -> normalized_P
VPoly vcone_to_vpoly(Matrix vcone) {
  VPoly result;
  result.U = sliced_fourier_motzkin(vcone, slice(1,U.d,1));
  result.V = normalized_P(vcone);
  return result;
}

// transformations

VPoly hpoly_to_vpoly(Matrix hpoly) {
  return vcone_to_vpoly(
           hcone_to_vcone(
             hpoly_to_hcone(move(hpoly))));
}

Matrix vpoly_to_hpoly(VPoly vpoly) {
  return hcone_to_hpoly(
           vcone_to_hcone(
             vpoly_to_vcone(move(vpoly))));
}
