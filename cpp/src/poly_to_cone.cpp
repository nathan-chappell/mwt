//poly_to_cone.cpp

#include "poly_to_cone.h"
#include "fourier_motzkin.h"

#include <algorithm>

using namespace std;

// project 0-th coordinate
Matrix project_zero(Matrix M) {
  transform(M.begin(), M.end(), M.begin(),
    [](const Vector &v) { return v[slice(1,v.size()-1,1)]; });
  return M;
}

//  ?    1
//  U -> V
Matrix normalize_P(Matrix M) {
  Matrix result;
  copy_if(M.begin(), M.end(), back_inserter(result),
    [](const Vector &v) { return v[0] > 0; });
  for (auto &&v : result) {
    if (v[0] != 1) {
      v /= v[0];
    }
  }
  return result;
}

// HP -> HC
// A|b -> -b|A
Matrix hpoly_to_hcone(Matrix hpoly) {
  transform(hpoly.begin(), hpoly.end(), hpoly.begin(),
      [](const Vector &v) { 
        auto tmp = v.cshift(-1); 
        tmp[0] *= -1;
        return tmp;
      });
  return hpoly;
}

// HC -> HP
// -b|A -> A|b 
Matrix hcone_to_hpoly(Matrix hpoly) {
  transform(hpoly.begin(), hpoly.end(), hpoly.begin(),
      [](const Vector &v) { 
        auto tmp = v.cshift(1); 
        tmp[tmp.size()-1] *= -1;
        return tmp;
      });
  return hpoly;
}

// VP -> VC
// U -> |0 1|
//      |U V|
Matrix vpoly_to_vcone(VPoly vpoly) {
  Matrix result;
  for (auto &&v : vpoly.U) {
    result.emplace_back(v.size()+1);
    result.back()[0] = 0;
    copy(begin(v), end(v), next(begin(result.back())));
  }
  for (auto &&v : vpoly.V) {
    result.emplace_back(v.size()+1);
    result.back()[0] = 0;
    copy(begin(v), end(v), next(begin(result.back())));
  }
  return result;
}

// VC -> VP
// U -> {Z \cup P*N, P'}
VPoly vcone_to_vpoly(Matrix vcone) {
  VPoly result;
  result.U = fourier_motzkin(vcone, 0);
  for (auto &&v : vcone) {
    //handle case v[0] == 1 separately to avoid floating point shenanigans
    if (v[0] == 1) {
      result.V.push_back(v[slice(1,v.size()-1,1)]);
    } else if (v[0] > 1) {
      result.V.push_back(v[slice(1,v.size()-1,1)]);
      result.V.back() /= v[0];
    }
  }
  return result;
}

