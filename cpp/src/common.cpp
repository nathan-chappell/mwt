//common.cpp

#include "common.h"

#include <algorithm>

using namespace std;

//dimension of space
size_t d;

// read in Vector
istream& operator>>(istream& i, Vector &v) {
  v.resize(d);
  for (size_t j = 0; j < d; ++j) {
    cin >> v[j];
  }
  if (cin.fail()) {
    throw input_error{"failed to read vector"};
  }
  return i;
}

// read in Matrix
istream& operator>>(istream& i, Matrix &M) {
  cin >> d;
  if (d <= 0) {
    throw input_error{"bad d: "s + to_string(d)};
  }
  Vector v;
  try{
    while (cin >> v) {
      M.push_back(move(v));
      cin >> ws;
      if (cin.eof()) break;
    }
  } catch (input_error e) {
    cerr << "error reading matrix, vector " << M.size() << endl;
    cerr << M.back() << endl;
    throw;
  }
  return i;
}

// read in VPoly
istream& operator>>(istream& i, VPoly &vcone) {
  bool reading_U{true};
  cin >> d;
  if (d <= 0) {
    throw input_error{"bad d: "s + to_string(d)};
  }
  Vector v;
  try{
    while (cin >> v) {
      if (reading_U) {
        vcone.U.push_back(move(v));
      } else {
        vcone.V.push_back(move(v));
      }
      cin >> ws;
      if (cin.eof()) break;
      if (cin.peek() == 'V') {
        cin.get();
        reading_U = false;
      }
    }
  } catch (input_error e) {
    cerr << "error reading matrix, vector " 
         << vcone.U.size() + vcone.V.size() << endl;
    cerr << (vcone.V.empty() ? vcone.U.back() : vcone.V.back()) << endl;
    throw;
  }
  return i;
}

// output Vector
ostream& operator<<(ostream& o, const Vector& v) {
  for (auto &&val : v) {
    o << val << " ";
  }
  return o;
}

// output Matrix
ostream& operator<<(ostream& o, const Matrix& M) {
  o << d << endl;
  for (auto &&v : M) {
    o << v << endl;
  }
  return o;
}

// output VPoly
ostream& operator<<(ostream& o, const VPoly &vcone) {
  o << d << endl;
  for (auto &&v : vcone.U) {
    o << v << endl;
  }
  if (vcone.V.empty()) {
    return o;
  } else {
    o << "V" << endl;
  }
  for (auto &&v : vcone.V) {
    o << v << endl;
  }
  return o;
}
int usage() {
  cerr << "usage: (vcone_to_hcone | vpoly_to_hpoly | hcone_to_vcone |"
       << "hpoly_to_vpoly)" << endl;
  cerr << "input is read on stdin,"
       << "transformed object written on stdout" << endl;
  cerr << "input format is as follows:\n " << endl;
  cerr << "hcone, vcone:= dimension   (vector)*" << endl;
  cerr << "       hpoly:= dimension+1 (vector constraint)*" << endl;
  cerr << "       vpoly:= dimension   (vector)* 'U' (vector)*\n" << endl;
  cerr << "dimension   is a positive integer" << endl;
  cerr << "vector      is (dimension) doubles separated by whitespace" << endl;
  cerr << "constraint  is a double (the value b_i in <A_i,x> <= b_i)" << endl;
  cerr << "hvector     is (dimension) doubles separated by whitespace" << endl;
  cerr << "'U'         is the literal character 'U'" << endl;
  return 0;
}

// Fourier Motzkin Elimation

// true if matrix or first row is empty
bool check_empty_matrix(const Matrix &M) {
  return (M.empty() || !M.front().size());
}

// Matrix transpose
Matrix transpose(const Matrix &M) {
  if (check_empty_matrix(M)) {
    return Matrix{};
  }
  Matrix result;
  const size_t rows = M.size();
  const size_t columns = M.front().size();
  for (size_t k = 0; k < columns; ++k) {
    result.emplace_back(rows);
  }
  size_t cur_row{0};
  for (auto &&result_row : result) {
    size_t cur_col{0};
    for (auto &&row : M) {
      result_row[cur_col++] = row[cur_row];
    }
    ++cur_row;
  }
  return result;
}

// keep only the first d elements of each vector
Matrix project_matrix(const Matrix &M) {
  Matrix result;
  for (auto &&row : M) {
    result.emplace_back(d);
    copy_n(begin(row), d, begin(result.back()));
  }
  return result;
}

// Fourier Motzkin Elimation on index k
Matrix fourier_motzkin(Matrix M, size_t k) {
  Matrix result;
  // Partition into Z,P,N
  const auto z_end = partition(M.begin(),M.end(),
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

