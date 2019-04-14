CC          = g++ -std=c++14
HEADERS_DIR = include
SOURCE_DIR  = src
TEST_DIR    = testing
CPPFLAGS    = -Wall -g -Og -I$(HEADERS_DIR)
OBJS_       = polyhedra polyhedra_common fourier_motzkin cone_base \
                hcone vcone vpolyhedron hpolyhedron mwt
OBJS        = $(OBJS_:%=$(SOURCE_DIR)/%.o)
TEST        = test.o

all                    : objs testing/test testing/parser_testing

testing/test           : testing/test.o $(OBJS) $(OBJS)

testing/parser_testing : testing/parser_testing.o $(OBJS)

objs                   : $(OBJS)

