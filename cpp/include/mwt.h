// mwt.h
#pragma once

#include "generics.h"
#include "fourier_motzkin.h"
#include "polyhedra.h"

#include <set>
#include <vector>

/*
 * Algorithms relevant to the mwt.  Many are wrapped in struct to create
 * functors.  These are for use with the generic algorithms from generics.h
 */

class LiftedCone : public cone_base { 
  std::vector<size_t> lifted_dimensions;
public:
  LiftedCone(math_vectors &&mvs, size_t);
  std::vector<size_t> get_dimensions() const { return lifted_dimensions; }
};

struct LiftedVCone : public LiftedCone {
  LiftedVCone(math_vectors &&mvs, size_t);
};
struct LiftedHCone : public LiftedCone {
  LiftedHCone(math_vectors &&mvs, size_t);
};

VCone       relax    (const VPolyhedron &);
LiftedVCone lift     (const VCone &);
HCone       drop     (const LiftedVCone &);
HPolyhedron restrict (const HCone &);

HCone       relax    (const HPolyhedron &);
LiftedHCone lift     (const HCone &);
VCone       drop     (const LiftedHCone &);
VPolyhedron restrict (const VCone &);

math_vector  prepend_value     (const math_vector &, math_vector::value_type);
math_vector  relax_constraint  (const constraint_vector&);
math_vectors relax_constraints (const constraint_vectors&);
constraint_vector  reconstrain (const math_vector&);
constraint_vectors reconstrain (const math_vectors&);

math_vectors normalize_k (math_vectors, const size_t&);

/*
 * The following functors just wrap the above functions.
 * This is for passing them to generic algorithms...
 */

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

