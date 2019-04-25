//transforms.h

#include "common.h"

// fourier motzkin for cones
Matrix hcone_to_vcone (Matrix hcone);
Matrix vcone_to_hcone (Matrix vcone);

// fourier motzkin for polyhedra
VPoly  hpoly_to_vpoly (Matrix hpoly);
Matrix vpoly_to_hpoly (VPoly vpoly);
