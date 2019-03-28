// mwt.h
#pragma once

#include "generics.h"
#include "polyhedra.h"

/*
 * Algorithms relevant to the mwt.  Many are wrapped in struct to create
 * functors.  These are for use with the generic algorithms from generics.h
 */

struct LiftedVCone { /* TODO */ };
struct LiftedHCone { /* TODO */ };

VCone       relax    (const VPolyhedron &);
LiftedVCone lift     (const VCone &);
HCone       drop     (const LiftedVCone &);
HPolyhedron restrict (const HCone &);

HCone       relax    (const HPolyhedron &);
LiftedHCone lift     (const HCone &);
VCone       drop     (const LiftedHCone &);
VPolyhedron restrict (const VCone &);


struct F_relax_VPolyhedron {
	VCone operator()(const VPolyhedron &VP) {
		return relax(VP);
	}
};

struct F_lift_VCone {
	LiftedVCone operator()(const VCone &VC) {
		return lift(VC);
	}
};

struct F_drop_LiftedVCone {
	HCone operator()(const LiftedVCone &Li) {
		return drop(Li);
	}
};

struct F_restrict_HCone {
	HPolyhedron operator()(const HCone &HC) {
		return restrict(HC);
	}
};


struct F_relax_HPolyhedron {
	HCone operator()(const HPolyhedron &HP) {
		return relax(HP);
	}
};

struct F_lift_HCone {
	LiftedHCone operator()(const HCone &HC) {
		return lift(HC);
	}
};

struct F_drop_LiftedHCone {
	VCone operator()(const LiftedHCone &Li) {
		return drop(Li);
	}
};

struct F_restrict_VCone {
	VPolyhedron operator()(const VCone &VC) {
		return restrict(VC);
	}
};

