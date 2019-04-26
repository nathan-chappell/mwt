//hcone.h

#include "common.h"

//number of generators in cone
extern size_t m;

// V-Cone -> H-Cone operations
namespace HCone {

// represent hcone as projection of hcone
Matrix lift_hcone(const Matrix &hcone);

// intersect vcone with {x_k = 0 | d+1 <= k <= d+m}
Matrix intersect_vcone(Matrix &&vcone);

} //namespace

Matrix hcone_to_vcone (Matrix hcone);
