//hcone_to_vcone.cpp

// H-Cone -> V-Cone operations
namespace {

//          d  d m
//  d     d|I -I 0|
//m|A| -> m|A -A I|
//
Matrix lift_hcone(const Matrix &M) {
  Matrix result;
  return result;
}
Matrix intersect_vcone(const Matrix &M) {
  Matrix result;
  return result;
}

Matrix project_vcone(const Matrix &M) {
  Matrix result;
  return result;
}
} //namespace


Matrix hcone_to_vcone(const Matrix &M) {
  if (check_empty_matrix(M)) {
    throw logic_error{"empty vcone"};
  }
  Matrix result;
  m_ = M.size();
  d_ = M.front().size();
  result = lift_hcone(M);
  result = intersect_vcone(result);
  result = project_vcone(result);
  return result;
}
