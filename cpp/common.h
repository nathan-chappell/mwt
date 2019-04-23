//common.h

#include <iostream>
#include <stdexcept>
#include <valarray>
#include <vector>

using Vector = std::valarray<double>;
using Matrix = std::vector<Vector>;
extern int dimension;

std::ostream& operator<<(std::ostream& o, const Vector&);
std::ostream& operator<<(std::ostream& o, const Matrix&);
