// mwt.cc

#include "mwt.h"

#include <iostream>

using namespace std;

VCone relax (const VPolyhedron &) {
	cout << "relaxing VPolyhedron" << endl;
	return VCone{};
}
LiftedVCone lift (const VCone &) {
	cout << "lifting VCone" << endl;
	return LiftedVCone{};
}
HCone drop (const LiftedVCone &) {
	cout << "dropping LiftedVCone" << endl;
	return HCone{};
}
HPolyhedron restrict (const HCone &) {
	cout << "restricting HCone" << endl;
	return HPolyhedron{};
}

HCone relax (const HPolyhedron &) {
	cout << "relaxing HPolyhedron" << endl;
	return HCone{};
}
LiftedHCone lift (const HCone &) {
	cout << "lifting HCone" << endl;
	return LiftedHCone{};
}
VCone drop (const LiftedHCone &) {
	cout << "dropping LiftedHCone" << endl;
	return VCone{};
}
VPolyhedron restrict (const VCone &) {
	cout << "restricting VCone" << endl;
	return VPolyhedron{};
}
