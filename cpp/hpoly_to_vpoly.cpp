//hpoly_to_vpoly.cpp

#include "transforms.h"

#include <algorithm>
#include <iostream> 

using namespace std;

int main(int argc, char **argv) {
  if (argc > 1) {
    return usage();
  }
  Matrix hpoly;
  cin >> hpoly;
  cout << hpoly_to_vpoly(move(hpoly));
}
