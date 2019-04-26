//hcone_to_hcone.cpp

#include "hcone.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  if (argc > 1) {
    return usage();
  }
  Matrix hcone;
  cin >> hcone;
  cout << hcone_to_vcone(hcone);
}
