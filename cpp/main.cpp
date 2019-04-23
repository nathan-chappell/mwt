//mwt.cpp

#include "mwt.h"

#include <stdexcept>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  try {
  read_args(argc, argv);
  read_input();
  } catch (invalid_argument e) {
    usage();
    cerr << "\nmessage: " << e.what() << endl;
    return -1;
  } catch (input_error e) {
    cerr << "invalid input: " << e.what() << endl;
    cerr << "reading vector: " << matrix_in.size() << endl;
  }
  transform();
  output_result();
}
