// fourier_motzkin.h
#pragma once

#include "linear_algebra.h"

// Fourier Motzkin Elimation on index k
Matrix fourier_motzkin(Matrix, size_t k);

// Fourier Motzkin for each index NOT in slice, then slice the result
Matrix sliced_fourier_motzkin(Matrix, const std::slice&);

// refactored lift operation
//
//  transforms set of column vectors as so:
//
//            ___d__ ___n__
//   n     n|     0 C[0]*I|
// d|U| -> d|C[1]*I C[2]*U|
//         d|C[3]*I C[4]*U|
//
//  transforms set of row vectors as so:
//
//           ___n__ ___d__ ___d__
//   d     d|     0 C[1]*I C[3]*I|
// n|A| -> n|C[0]*I C[2]*A C[4]*A|
//
Matrix generalized_lift(const Matrix &cone, const std::array<double,5> &C);

// represent vcone as projection of hcone
//             d  p
//    p     p| 0 -I|
// d |U| -> d| I -U|
//          d|-I  U|
//
Matrix lift_vcone(const Matrix &vcone);

// represent hcone as projection of vcone
//           m d  d
//   d     d|0 I -I|
// m|A| -> m|I A -A|
//
Matrix lift_hcone(const Matrix &hcone);

// used to statically select lift as opposed to using fn pointer
enum class LiftSelector { lift_vcone, lift_hcone };

// refactored transformation algorithm
Matrix cone_transform(const Matrix &cone, LiftSelector);

Matrix vcone_to_hcone(Matrix vcone);
Matrix hcone_to_vcone(Matrix hcone);
