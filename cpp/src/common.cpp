//common.cpp

#include "common.h"

#include <algorithm>
#include <fstream>

using namespace std;

// Vector utilities

// basis vectors
Vector e_k(size_t d, size_t k) {
  Vector result(d);
  result[k] = 1;
  return result;
}

// concatentation
Vector concatenate(const Vector &l, const Vector &r) {
  Vector result(l.size() + r.size());
  copy(begin(l), end(l), begin(result));
  copy(begin(r), end(r), next(begin(result), l.size()));
}

// struct Matrix

void Matrix::push_back(const Vector &v) { 
  if (v.size() != d) {
    throw std::out_of_range{"v.size() != d"};
  }
  vectors.push_back(v); 
}

void Matrix::push_back(Vector &&v) { 
  if (v.size() != d) {
    throw std::out_of_range{"v.size() != d"};
  }
  vectors.push_back(move(v)); 
}

// read in Vector
// Vector must be correct size before reading
istream& operator>>(istream& i, Vector &v) {
  for (auto &v_i : v) {
    in >> v_i;
  }
  if (i.fail()) {
    throw input_error{"failed to read vector: istream failed"};
  }
  return i;
}

// read in Matrix
// Matrix must have d set before reading (enforced by constructor)
istream& operator>>(istream& i, Matrix &M) {
  try{
    do {
      i >> M.add_Vector() >> ws;
    } while (i.good());
  } catch (input_error e) {
    cerr << "error reading matrix, vector " << M.size() << endl;
    throw;
  }
  if (i.fail()) {
    throw input_error{"failed to read matrix: istream failed"};
  }
  return i;
}

// read in VPoly
// vpoly must have d set before reading (enforced by constructor)
istream& operator>>(istream& i, VPoly &vpoly) {
  // determines which Matrix gets the next vector
  bool reading_U{true};
  char who{0};
  try {
    do {
      // check for U/V, get next vector and ws
      if (who == 'V' || (i.peek() == 'V' && who = i.get())) {
        i >> vpoly.V.add_Vector() >> ws;
      else if (who == 'U' || (i.peek() == 'U' && who = i.get())) {
        i >> vpoly.U.add_Vector() >> ws;
      } else {
        throw input_error{"neither U (rays) nor V (points) chosen"};
      }
    } while (i.good());
  } catch (input_error e) {
    cerr << "error reading matrix, vector " 
         << vpoly.U.size() + vpoly.V.size() << endl;
    throw;
  }
  if (i.fail()) {
    throw input_error{"failed to read vpoly: istream failed"};
  }
  return i;
}

// output Vector
ostream& operator<<(ostream& o, const Vector& v) {
  for (auto &&val : v) { o << val << " "; }
  return o;
}

// output Matrix
ostream& operator<<(ostream& o, const Matrix& M) {
  o << M.d << endl;
  for (auto &&v : M) { o << v << endl; }
  return o;
}

// output VPoly
ostream& operator<<(ostream& o, const VPoly &vpoly) {
  o << vpoly.d << endl;
  if (!vpoly.U.empty()) {
    o << "U" << endl;
    for (auto &&u : vpoly.U) { o << u << endl; }
  }
  if (!vpoly.V.empty()) {
    o << "V" << endl;
    for (auto &&v : vpoly.V) { o << v << endl; }
  }
  return o;
}

size_t read_dimension(std::istream &i) {
  int d;
  i >> d;
  if (d <= 0) {
    throw input_error{"bad d: "s + to_string(d)};
  }
  return static_cast<size_t>(d);
}

// factory needed because const member must be set for operator>> to work
Matrix Matrix::read_Matrix(std::istream& i) {
  Matrix result{read_dimension(i)};
  i >> result;
  return result;
}

// factory needed because const member must be set for operator>> to work
VPoly VPoly::read_VPoly(std::istream& i) {
  VPoly result{read_dimension(i)};
  i >> result;
  return result;
}

// If I had to write that one more time I'd templatize it...

int usage() {
  cerr << ifstream{"usage.txt"}.rdbuf();
  return 0;
}

// Matrix utilities

// column selection
Vector get_column(const Matrix &M, size_t k) {
  if (!(0 <= k && k < M.d)) {
    throw std::out_of_range("k < 0 || M.d <= k");
  }
  Vector result(M.size());
  size_t result_row{0};
  for (auto &&row : M) {
    result[result_row++] = row[k];
  }
  return result;
}

// Matrix transpose
Matrix transpose(Matrix M) {
  if (M.empty()) {
    return M;
  }
  Matrix result{M.size()};
  // for every column of M,
  for (size_t k = 0; k < M.d; ++k) {
    result.push_back(get_column(M,k));
  }
  return result;
}

// slice each vector in M with s
Matrix slice_matrix(const Matrix &M, const std::slice &s) {
  Matrix result{s.size()};
  transform(M.begin(), M.end(), result.begin(),
    [s](const Vector &v) { return v[s]; });
  return result;
}

// true iff index is "a member of" slice
bool index_in_slice(size_t index, const slice &s) {
  return (s.start() <= index && 
          index <= s.start() + s.stride()*(s.size()-1) &&
          (index - s.start()) % s.stride() == 0);
}

// Fourier Motzkin Elimation

// Fourier Motzkin Elimation on index k
Matrix fourier_motzkin(Matrix M, size_t k) {
  Matrix result;
  // Partition into Z,P,N
  const auto z_end = partition(M.begin(), M.end(),
      [k](const Vector &v) { return v[k] == 0; });
  const auto p_end = partition(z_end, M.end(),
      [k](const Vector &v) { return v[k] > 0; });
  // Move Z to result
  move(M.begin(), z_end, back_inserter(result));
  // convolute vectors from P,N
  for (auto p_it = z_end; p_it != p_end; ++p_it) {
    for (auto z_it = p_end; z_it != M.end(); ++z_it) {
      result.push_back( 
        (*p_it)[k]*(*z_it) - (*z_it)[k]*(*p_it));
    } 
  } 
  return result;
}

// Fourier Motzkin, on each index not in slice, then slice the result
Matrix sliced_fourier_motzkin(Matrix M, const slice &s) {
  for (size_t k = 0, k < M.d, ++k) {
    if (!index_in_slice(k,s)) {
      M = fourier_motzkin(M, k);
    }
  }
  return slice_matrix(M, s);
}

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
Matrix generalized_lift(const Matrix &cone, const array<double,5> &C) {
  const size_t d = cone.d;
  const size_t n = cone.size();
  Matrix result{d+n};
  Matrix cone_t = transpose(cone);
  // |0  C[0]*I|  |0     |
  //              |C[0]*I|
  for (size_t i = 0; i < n; ++i) {
    result.add_Vector()[d+i] = C[0];
  }
  size_t k = 0;
  // |C[1]*I C[2]*U|  |C[1]*I|
  //                  |C[2]*A|
  for (auto &&row_t : cone_t) {
    result.push_back(concatenate(C[1]*e_k(d,k++), C[2]*row)
  }
  k = 0;
  // |C[3]*I C[4]*U|  |C[3]*I|
  //                  |C[4]*A|
  for (auto &&row_t : cone_t) {
    result.push_back(concatenate(C[3]*e_k(d,k++), C[4]*row));
  }
  return result;
}

// represent vcone as projection of hcone
//             d  p
//    p     p| 0 -I|
// d |U| -> d| I -U|
//          d|-I  U|
//
Matrix lift_vcone(const Matrix &vcone) {
  return generalized_lift(vcone, {-1,1,-1,-1,1});
}

// represent hcone as projection of vcone
//           m d  d
//   d     d|0 I -I|
// m|A| -> m|I A -A|
//
Matrix lift_hcone(const Matrix &hcone) {
  return generalized_lift(vcone, {1,1,1,-1,-1});
}

// refactored transformation algorithm
Matrix cone_transform(const Matrix &cone, 
                         Matrix(*lift)(const Matrix&)) {
  if (cone.empty()) {
    throw logic_error{"empty cone for transform"};
  }
  // the idea of the entire mwt is this one line
  return sliced_fourier_motzkin(lift(cone), slice(0, cone.d, 1));
}

Matrix vcone_to_hcone(Matrix vcone) {
  return cone_transform(cone,lift_vcone);
}

Matrix hcone_to_vcone(Matrix hcone) {
  return cone_transform(cone,lift_hcone);
}

