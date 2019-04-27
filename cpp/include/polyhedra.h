//polyhedra.h

#include "common.h"

// HP -> HC
// A|b -> -b|A
Matrix hpoly_to_hcone(Matrix hpoly);

// HC -> HP
// -b|A -> A|b 
Matrix hcone_to_hpoly(Matrix hpoly);

// VP -> VC
// U -> |0 1|
//      |U V|
Matrix vpoly_to_vcone(VPoly vpoly);

// VC -> VP
// U -> {Z \cup P*N, P'}
VPoly vcone_to_vpoly(Matrix vcone);

// transformations
VPoly  hpoly_to_vpoly(Matrix hpoly);
Matrix vpoly_to_hpoly(VPoly vpoly);
