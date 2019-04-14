//generics.h
#pragma once

/*
 * Generic algorithms for:
 *  lift and drop
 *  relax, lift and drop, restrict
 *
 *  All functors require default constructors
 */

/*
 * The representation type (Rep) and the alternate representation type
 * (not named here) are deduced.
 */
template <
          typename LiftFunctor,
          typename DropFunctor,
          typename Rep 
          >
auto lift_and_drop(const Rep &rep) {
  auto &&altRep = LiftFunctor{}(rep);
  return DropFunctor{}(altRep);
}

/*
 * The representation type (Rep) and the alternate representation type
 * (not named here) are deduced.
 */
template <
          typename RelaxFunctor,
          typename LiftFunctor,
          typename DropFunctor,
          typename RestrictFunctor,
          typename Rep
          >
auto relax_lift_drop_restrict(const Rep &rep) {
  auto &&relaxed = RelaxFunctor{}(rep);
  auto &&alt = lift_and_drop<LiftFunctor,DropFunctor>(relaxed);
  return RestrictFunctor{}(alt);
}
