//parser_testing.cc

#include "test_cases.h"

#include "polyhedra.h"

#include <iomanip>
#include <sstream>

using namespace std;

size_t Test::id{0};

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

void test_failure(const Test &test, const string &m) {
  cout << "failed: " << test << endl;
  cout << "message: " << m << "\n" << std::string(40, '-') << endl;
  ++test_failures;
}

template <typename T>
void run_tests(const list<Test> &tests) {
  for (auto &&test : tests) {
    try {
      istringstream iss{test.input};
      T t;
      t.read_in(iss, nullptr);
    } catch (polyhedra_read_error e) {
      switch(test.type) {
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
    if (test.type == test_type::bad) {
      //bad test without error
      test_failure(test, "(no exception)");
    }
  }
}

int main() {
  cout << "running tests\n" << endl;
  run_tests<VCone>(cone_base_tests);
  progress();
  run_tests<HCone>(cone_base_tests);
  progress();
  run_tests<HPolyhedron>(hpolyhedron_tests);
  progress();
  run_tests<VPolyhedron>(vpolyhedron_tests);
  progress();
}
