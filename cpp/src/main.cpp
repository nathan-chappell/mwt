// main.cpp

#include "polyhedra.h"

#include <string>

using namespace std;

void vc_to_hc() {
  cout << vcone_to_hcone(Matrix::read_Matrix(cin));
}

void hc_to_vc() {
  cout << hcone_to_vcone(Matrix::read_Matrix(cin));
}

void vp_to_hp() {
  cout << vpoly_to_hpoly(VPoly::read_VPoly(cin));
}

void hp_to_vp() {
  cout << hpoly_to_vpoly(Matrix::read_Matrix(cin));
}

int main(int argc, char **argv) {
  if (argc != 2) {
    return usage();
  } else if (argv[1] == "vc_to_hc"s) {
    vc_to_hc();
  } else if (argv[1] == "hc_to_vc"s) {
    hc_to_vc();
  } else if (argv[1] == "vp_to_hp"s) {
    vp_to_hp();
  } else if (argv[1] == "hp_to_vp"s) {
    hp_to_vp();
  } else {
    return usage();
  }
}
