//fourier_motzkin.h
#pragma once

#include "common.h"

// keep only the first d elements of each vector
Matrix project_matrix(const Matrix &M);

// Fourier Motzkin Elimation on index k
Matrix fourier_motzkin(Matrix M, size_t k);
