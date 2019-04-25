//vpoly_to_hpoly.cpp

#include "transforms.h"

#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  if (argc > 1) {
    return usage();
  }
  VPoly vpoly;
  cin >> vpoly;
  cout << vpoly_to_hpoly(move(vpoly));
}
