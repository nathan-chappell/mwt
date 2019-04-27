//hcone.h

#include "common.h"

// V-Cone -> H-Cone operations
namespace HCone {

// represent hcone as projection of vcone
//           d  d m
//   d     d|I -I 0|
// m|A| -> m|A -A I|
//
Matrix lift_hcone(Matrix hcone);

// intersect vcone with {x_k = 0 | d+1 <= k <= d+m}
Matrix intersect_vcone(Matrix vcone);

} //namespace

Matrix hcone_to_vcone (Matrix hcone);
