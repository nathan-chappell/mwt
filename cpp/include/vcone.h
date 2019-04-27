//vcone.cpp

#include "common.h"

// V-Cone -> H-Cone operations
namespace VCone {

// represent vcone as projection of hcone
Matrix lift_vcone(const Matrix &vcone);

// project away d+1 to p
Matrix project_hcone(Matrix &&hcone);

} //namespace

Matrix vcone_to_hcone (Matrix vcone);
