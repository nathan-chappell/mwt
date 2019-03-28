//test_cases.h

#include <list>
#include <iostream>
#include <iomanip>
#include <sstream>

enum class test_type {good, bad};

struct Test {
  static size_t id;

  test_type type;
  size_t test_id;
  std::string input;

  Test(test_type type, const std::string &input) 
        : type{type}, test_id{++id}, input{input} {}
};

std::ostream &operator<<(std::ostream &o, const Test &test) {
  o << std::setw(3) << test.test_id << " ";
  switch(test.type) {
    case test_type::good: o << "good:\n"; break;
    case test_type::bad:  o << " bad:\n "; break;
  }
  return o << test.input;
}

std::list<Test> cone_base_tests {
  {test_type::bad,  "2 1"},
  {test_type::bad,  "2 1q"},
  {test_type::bad,  "2 1 q"},
  {test_type::bad,  "2 1 2 3.1"},
  {test_type::bad,  "2 1 2 3.1 q"},
  {test_type::bad,  "2 1 2x"},
  {test_type::bad,  "2 1 2 x"},
  {test_type::bad,  "2 1 2 3.1 0.x"},
  {test_type::bad,  "2 1 2 3.1 0. x"},
  {test_type::good, "2 1 2"},
  {test_type::good, "2 1 2q"},
  {test_type::good, "2 1 2 q"},
  {test_type::good, "2 1 2 3.1 0."},
  {test_type::good, "2 1 2 3.1 0.q"},
  {test_type::good, "2 1 2 3.1 0. q"},
};

std::list<Test> hpolyhedron_tests {
  {test_type::good, "2 1 2 <= 1"},
  {test_type::good, "2 1 2 <= 1q"},
  {test_type::good, "2 1 2 <= 1 q"},
  {test_type::good, "2 1 2 <= 1"},
  {test_type::good, "2 1 2 <= -.2 1.1 -2.3 <= 1q"},
  {test_type::bad,  "2 1 2"},
  {test_type::bad,  "2 1 2 <= 1 2"},
  {test_type::bad,  "2 1 2 <= q"},
  {test_type::bad,  "2 1 2 <= "}
};

std::list<Test> vpolyhedron_tests {
  {test_type::good, "2 1 2"},
  {test_type::good, "2 1 2q"},
  {test_type::good, "2 1 2 V 1 2q"},
  {test_type::good, "2 1 2 V 1 2 q"},
  {test_type::bad,  "2 1"},
  {test_type::bad,  "2 1q"},
  {test_type::bad,  "2 1 2 V 1 q"},
  {test_type::bad,  "2 1 2 V -.1 2 3.3q"}
};

