//mwt.h

#include "common.h"

extern Matrix matrix_in;

class input_error : public std::runtime_error {
public:
  input_error(const char*s) : std::runtime_error{s} {}
};

enum class InputType {VCone, HCone, VPolyhedron, HPolyhedron};
extern InputType inputType;

void usage();
void read_args(int argc, char* argv[]);
void read_input();
void transform();
void output_result();
