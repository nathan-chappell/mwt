//test.cc

#include "polyhedra.h"

using namespace std;

const string line_break(40,'-');

int main(int argc, char *argv[]) {
  HCone hcone;
  hcone.read_interactive();
  cout << "hcone:\n" << hcone << line_break << endl;
  VCone vcone;
  vcone.read_interactive();
  cout << "vcone:\n" << vcone << line_break << endl;
}
