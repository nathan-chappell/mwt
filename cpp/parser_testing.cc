//parser_testing.cc

#include "vcone.h"

#include <iomanip>
#include <sstream>

using namespace std;

using test_name = string;
using test_item = string;
using test_case = pair<test_name, test_item>;

int test_count;
int test_failures;

void progress(ostream& o = cout) {
  auto flags = o.flags();
  o << left << setfill('.');
  o << setw(20) << "test_count" << test_count << "\n";
  o << setw(20) << "test_failures" << test_failures << "\n";
  o << endl;
  o.flags(flags);
}

enum class test_type {good, bad};

namespace cone_tests {
list<test_case> bad_cases{
  {"cone_1", "2 1"},
  {"cone_2", "2 1q"},
  {"cone_3", "2 1 q"},
  {"cone_4", "2 1 2 3.1"},
  {"cone_5", "2 1 2 3.1 q"},
  {"cone_6", "2 1 2x"},
  {"cone_7", "2 1 2 x"},
  {"cone_8", "2 1 2 3.1 0.x"},
  {"cone_9", "2 1 2 3.1 0. x"},
};

list<test_case> good_cases{
  {"cone_1", "2 1 2"},
  {"cone_2", "2 1 2q"},
  {"cone_3", "2 1 2 q"},
  {"cone_4", "2 1 2 3.1 0."},
  {"cone_5", "2 1 2 3.1 0.q"},
  {"cone_5", "2 1 2 3.1 0. q"},
};

}; //cone_tests

void test_failure(const test_case &test, const string &m) {
  cout << "failed: " << test.first << endl;
  cout << "\tmessage: " << m << endl;
  ++test_failures;
}

template <typename T>
void run_tests(const list<test_case> &tests, test_type type) {
  for (auto &&test : tests) {
    istringstream iss{test.second};
    try {
      T t;
      t.read_in(iss, nullptr);
    } catch (polyhedra_read_error e) {
      switch(type) {
        case test_type::good: {
          //good test with error
          test_failure(test, e.what());
          continue;
        } break;
        case test_type::bad: {
          continue;
        } break;
      }
    }
    if (type == test_type::bad) {
      //bad test without error
      test_failure(test, "(no exception)");
    }
  }
}

int main() {
  cout << "running tests\n" << endl;
  cout << "vcone good tests" << endl;
  run_tests<VCone>(cone_tests::good_cases, test_type::good);
  progress();
  cout << "vcone bad tests" << endl;
  run_tests<VCone>(cone_tests::bad_cases, test_type::bad);
  progress();
}
