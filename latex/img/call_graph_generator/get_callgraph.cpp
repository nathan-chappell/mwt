// get_callgraph.cpp

#include "clang-c/Index.h"
#include "graph.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
  init();
  ofstream{"mwt.gv"} << graph::create_from_filenames(mwt_files) << endl;
  ofstream{"test.gv"} << graph::create_from_filenames(test_files) << endl;
  cleanup();
}
