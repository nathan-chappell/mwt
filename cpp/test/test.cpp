// test.cpp

#include "test_functions.h"
#include "polyhedra.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<cone_test_case> cone_tests { 
  { "upper-half first quadrant (hcone)",
    {{-1,0},{1,-1}},
    {{0,1},{1,1}},  
    hcone_to_vcone
  },
  { "origin",
    {{1,0},{-1,-1},{0,1}},
    {{0,0}},
    hcone_to_vcone
  },
  { "3-d pyramid (hcone)",
    {{1,1,-1},{-1,1,-1},{1,-1,-1},{-1,-1,-1}},
    {{0,1,1},{1,0,1},{0,-1,1},{-1,0,1}},
    hcone_to_vcone
  },
  { "upper-half first quadrant (vcone)",
    {{0,.1},{.1,.1}},
    {{-1,0},{.5,-.5}},  
    vcone_to_hcone
  },
  { "3-d pyramid (vcone)",
    {{0,1,1},{1,0,1},{0,-1,1},{-1,0,1}},
    {{1,1,-1},{-1,1,-1},{1,-1,-1},{-1,-1,-1}},
    vcone_to_hcone
  },
};

vector<hpoly_test_case> hpoly_tests {
  { "slice and shift first quadrant",
    {{-1,0,-1},{0,-1,-1},{-2,-1,-5}},
    { /*U*/{{1,0},{0,1}}, /*V*/{{1,3},{2,1}} }
  },
  { "square",
    {{-1,0,1},{0,-1,1},{1,0,1}, {0,1,1}},
    { /*U*/{}, /*V*/{{-1,-1},{-1,1},{1,-1},{1,1}} }
  },
  { "3-simplex",
    {{-1,0,0,1},{0,-1,0,1},{0,0,-1,1}, {1,1,1,1}},
    { /*U*/{}, /*V*/{{0,0,0},{1,0,0},{0,1,0},{0,0,1}} }
  },
};

// above tests flipped around
vector<vpoly_test_case> vpoly_tests {
  { "slice and shift first quadrant",
    { /*U*/{{1,0},{0,1}}, /*V*/{{1,3},{2,1}} },
    {{-1,0,-1},{0,-1,-1},{-2,-1,-5}}
  },
  { "square",
    { /*U*/{}, /*V*/{{-1,-1},{-1,1},{1,-1},{1,1}} },
    {{-1,0,1},{0,-1,1},{1,0,1}, {0,1,1}}
  },
  { "3-simplex",
    { /*U*/{}, /*V*/{{0,0,0},{1,0,0},{0,1,0},{0,0,1}} },
    {{-1,0,0,1},{0,-1,0,1},{0,0,-1,1}, {1,1,1,1}}
  },
};

void print_bool_vec(const vector<bool> &v) {
  for (auto b : v) {
    cout << b << ", ";
  }
  cout << endl;
}

void equivalence_fn_test() {
  int old_v = verbosity;
  verbosity = 0;
  vector<bool> results {
   is_equivalent({1,1,1},{2.2,2.2,2.2}),
  !is_equivalent({1,1,1},{2,2,1.9}),
   is_equal({1,1,1},{1,1,1}),
  !is_equal({1,1,1},{1,1,.9}),
   has_equivalent_member({{1,1,1},{2,3,1}},{2,2,2}),
   has_equivalent_member({{1,1,1},{2,3,1}},{1,1.5,.5}),
  !has_equivalent_member({{1,1,1},{2,3,1}},{1,1.5,-.5}),
   has_equal_member({{1,1,1},{2,3,1}},{2,3,1}),
  !has_equal_member({{1,1,1},{2,3,1}},{1,1.5,-.5}),
   subset_mod_eq({{1,1,1},{2,3,1}},{{1,1.5,.5}, {2,2,2}}),
  !subset_mod_eq({{1,1,1},{2,3,1}},{{1,1.5,.5}, {-2,2,2}}),
  };
  verbosity = old_v;
  cout << "eq test: " << count(results.begin(), results.end(), false) << endl;
  if (verbosity >= 1) { print_bool_vec(results); }
}

void satisfaction_fn_test() {
  int old_v = verbosity;
  verbosity = 0;
  vector<bool> results {
     ray_satisfied({1,0}, {0,1}),
    !ray_satisfied({1,2}, {-1,1}),
     ray_satisfied({{1,-2}, {-1,1}}, {1,1}),
    !ray_satisfied({{1,-2}, {-1,1}}, {1,2}),
     rays_satisfied({{1,-2}, {-1,1}}, {{1,1}, {2,1}}),
    !rays_satisfied({{1,-2}, {-1,1}}, {{2,1}, {-1,.9}}),
     vec_satisfied({1,1,3},{2,1}),
    !vec_satisfied({1,-1,3},{5,1}),
     vec_satisfied({{1,1,4},{0,1,2}},{2,2}),
    !vec_satisfied({{1,1,4},{0,1,2}},{3,2}),
     vecs_satisfied({{1,1,4},{0,1,2}},{{2,2},{5,-1}}),
    !vecs_satisfied({{1,1,4},{0,1,2}},{{1,2},{-3,3}}),
  };
  verbosity = old_v;
  cout << "sat test: " << count(results.begin(), results.end(), false) << endl;
  if (verbosity >= 1) { print_bool_vec(results); }
}

void transform_test() {
  size_t failures{0};
  for (auto &&test : cone_tests)  { failures += (!test.run_test()); }
  for (auto &&test : hpoly_tests) { failures += (!test.run_test()); }
  cout << "transform failures: " << failures << endl;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    string arg{argv[1]};
    verbosity = count(arg.begin(), arg.end(), 'v');
  }
  equivalence_fn_test();
  satisfaction_fn_test();
  transform_test();
}

