//mwt.cpp

#include "mwt.h"
#include "fourier_motzkin.h"

#include <iostream>

using namespace std;

InputType inputType;
Matrix matrix_in;
Matrix matrix_out;
int dimension;

void usage() {
  cerr << "usage: input_type input" << endl;
  cerr << "input_type:" << endl;
  cerr << "\t-VC\tvcone -> hcone\n";
  cerr << "\t-HC\thcone -> vcone\n";
  cerr << "\t-VP\tvpolyhedron -> hcone\n";
  cerr << "\t-HP\thpolyhedron -> vcone\n" << endl;
  cerr << 
"input is read on stdin, the first number should be the dimension of the object\n"
"to be transformed, the following numbers should be floating point numbers\n"
"representing the object" << endl;
}

void read_args(int argc, char* argv[]) {
  if (argc != 2) {
    throw invalid_argument("improper number of arguments");
  }
  if (argv[1] == "-VC"s) { inputType = InputType::VCone; }
  else if (argv[1] == "-HC"s) { inputType = InputType::HCone; }
  else if (argv[1] == "-VP"s) { inputType = InputType::VPolyhedron; }
  else if (argv[1] == "-HP"s) { inputType = InputType::HPolyhedron; }
  else {
    throw invalid_argument("unknown argument");
  }
}

void read_cone();

void read_dimension() {
  cin >> dimension;
  if (!cin || dimension <= 0) {
    throw input_error{"bad dimension"};
  }
}

void read_vector() {
  matrix_in.emplace_back(dimension);
  for (int i = 0; i < dimension; ++i) {
    cin >> matrix_in.back()[i];
    if (cin.eof()) {
      throw input_error{"not enough elements in vector"};
    }
  }
  if (!cin) {
    throw input_error{"cin failed!"};
  }
}

void read_input() {
  read_dimension();
  while (cin >> ws, cin.good()) {
    read_vector();
  }
}

void transform() {
  switch (inputType) {
    case InputType::VCone: {
      matrix_out = vcone_to_hcone(matrix_in);
    } break;
    case InputType::HCone: {
      matrix_out = hcone_to_vcone(matrix_in);
    } break;
    default: {
      throw std::logic_error{"shouldn't be here"};
    }
  }
}

void output_result() {
  cout << matrix_out << string(40,'-') << endl;
}
