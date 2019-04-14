//test.cc

#include "polyhedra.h"
#include "mwt.h"

using namespace std;

const string line_break(40,'-');

HCone hcone;
HPolyhedron hpoly;

void generic() {
  /*
  cout << "hcone: \n" << hcone << flush;
  cout << "HC -> VC" << endl;
  cout << lift_and_drop<
                      F_lift_HCone, 
                      F_drop_LiftedHCone
                      >(hcone);
  cout << line_break << endl;
  cout << "HC -> VC" << endl;
  VCone vc       = lift_and_drop<
                      F_lift_HCone, 
                      F_drop_LiftedHCone
                      >(hcone);
  cout << line_break << endl;
  */
  cout << "hpoly:" << endl;
  cout << hpoly << endl;
  cout << "HP -> VP" << endl;
  VPolyhedron vp = relax_lift_drop_restrict<
                      F_relax_HPolyhedron, 
                      F_lift_HCone, 
                      F_drop_LiftedHCone,
                      F_restrict_VCone
                      >(hpoly);
  cout << vp << endl;
  cout << line_break << endl;

/*
  cout << "VC -> HC" << endl;
  HCone hc       = lift_and_drop<
                      F_lift_VCone, 
                      F_drop_LiftedVCone
                      >(VCone{});
  cout << line_break << endl;

  cout << "VP -> HP" << endl;
  HPolyhedron hp = relax_lift_drop_restrict<
                      F_relax_VPolyhedron, 
                      F_lift_VCone, 
                      F_drop_LiftedVCone,
                      F_restrict_HCone
                      >(VPolyhedron{});
  cout << line_break << endl;
  */
}

int main(int argc, char *argv[]) {
  //hcone.read_interactive();
  //hcone.read_in(cin, nullptr);
  //hpoly.read_interactive();
  hpoly.read_in(cin, nullptr);
  generic();
}
