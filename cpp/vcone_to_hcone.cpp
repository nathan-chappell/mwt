//vcone_to_hcone.cpp

#include "transforms.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  if (argc > 1) {
    return usage();
  }
  Matrix vcone;
  cin >> vcone;
  cout << vcone_to_hcone(move(vcone));
}
