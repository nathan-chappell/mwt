CC = g++ -std=c++14
HEADERS = include
SOURCE = src
CPPFLAGS = -Wall -Og -I$(HEADERS)
#OBJ_PREFIX = polyhedra
#OBJS_ = hcone vcone hpolyhedron vpolyhedron
OBJS_ = polyhedra cone_base hcone vcone 
OBJS = $(OBJS_:%=$(SOURCE)/%.o)
TEST = test.o

all : test objs

test : test.o $(OBJS)

objs : $(OBJS)


