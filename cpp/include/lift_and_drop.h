//lift_and_drop.h
#pragma once

/*
 * Takes a representation, lifts it, then drops it
 * note: the trailing return type implies that DropFunctor and LiftFunctor
 * are default constructible
 */
template <
          typename LiftFunctor,
          typename DropFunctor,
          typename Rep 
          >
auto lift_and_drop(const Rep &rep) 
    -> decltype(DropFunctor{}(LiftFunctor{}(rep))) {
  auto &&altRep = LiftFunctor{}(rep);
  return DropFunctor{}(altRep);
}

