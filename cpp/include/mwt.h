// mwt.h
#pragma once

#include "generics.h"
#include "polyhedra.h"

#include <set>
#include <vector>

/*
 * Algorithms relevant to the mwt.  Many are wrapped in struct to create
 * functors.  These are for use with the generic algorithms from generics.h
 */

struct LiftedVCone { /* TODO */ };


class LiftedHCone : public HCone { 
  std::vector<size_t> lifted_dimensions;
public:
  LiftedHCone(math_vectors &&mvs, size_t);
  std::vector<size_t> get_dimensions() const { return lifted_dimensions; }
};

VCone       relax    (const VPolyhedron &);
LiftedVCone lift     (const VCone &);
HCone       drop     (const LiftedVCone &);
HPolyhedron restrict (const HCone &);

HCone       relax    (const HPolyhedron &);
LiftedHCone lift     (const HCone &);
VCone       drop     (const LiftedHCone &);
VPolyhedron restrict (const VCone &);

math_vector  relax_constraint  (const constraint_vector&);
math_vectors relax_constraints (const constraint_vectors&);

math_vector  fjoink_v    (const math_vector&, const math_vector&);
math_vector  project_K_v (const math_vector&, const std::vector<size_t>&);
math_vectors fjoin_k     (math_vectors, const size_t&);
math_vectors fjoin       (math_vectors, const std::vector<size_t>&);
math_vectors normalize_k (math_vectors, const size_t&);
math_vectors project_K   (const math_vectors&, std::vector<size_t>);


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

