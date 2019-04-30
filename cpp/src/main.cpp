// main.cpp

#include "polyhedra.h"

#include <string>

using namespace std;

int main(int argc, char **argv) {
  if (argc != 2) {
    cerr << "wrong number of args" << endl;
    return usage();
  } else if (argv[1] == "-vc"s) {
    cout << vcone_to_hcone(Matrix::read_Matrix(cin));
  } else if (argv[1] == "-hc"s) {
    cout << hcone_to_vcone(Matrix::read_Matrix(cin));
  } else if (argv[1] == "-vp"s) {
    cout << vpoly_to_hpoly(VPoly::read_VPoly(cin));
  } else if (argv[1] == "-hp"s) {
    cout << hpoly_to_vpoly(Matrix::read_Matrix(cin));
  } else {
    cerr << "improper arg" << endl;
    return usage();
  }
}
