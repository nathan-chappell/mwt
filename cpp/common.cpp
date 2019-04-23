//common.cpp

#include "common.h"

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

// true if matrix or first row is empty
bool check_empty_matrix(const Matrix &M) {
  return (M.empty() || !M.front().size());
}
