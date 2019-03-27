CC = g++ -std=c++14
HEADERS = include
SOURCE = src
CPPFLAGS = -Wall -Og -I$(HEADERS)
#OBJ_PREFIX = polyhedra
#OBJS_ = hcone vcone hpolyhedron vpolyhedron
OBJS_ = polyhedra polyhedra_common cone_base hcone vcone 
OBJS = $(OBJS_:%=$(SOURCE)/%.o)
TEST = test.o

all : test objs parser_testing

test : test.o $(OBJS)

objs : $(OBJS)

parser_testing : parser_testing.o $(OBJS)
