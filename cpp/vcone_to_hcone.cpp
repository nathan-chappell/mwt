//vcone_to_hcone.cpp

#include "vcone.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  if (argc > 1) {
    return usage();
  }
  int d;
  cin >> d;
  if (d <= 0) {
    throw input_error{"bad d: "s + to_string(d)};
  }
  Matrix vcone{static_cast<size_t>(d)};;
  cin >> vcone;
  cout << vcone_to_hcone(move(vcone));
}
