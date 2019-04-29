CC = g++ -std=c++14
CPPFLAGS = -g -Og -Wall -Iinclude
OBJS_ = polyhedra vcone hcone common
OBJS = $(OBJS_:%=src/%.o)

all : vcone_to_hcone hcone_to_vcone vpoly_to_hpoly hpoly_to_vpoly

vcone_to_hcone : $(OBJS) vcone_to_hcone.cpp
	$(CC) $@.cpp $(CPPFLAGS) $(OBJS) -o $@

hcone_to_vcone : $(OBJS) hcone_to_vcone.cpp
	$(CC) $@.cpp $(CPPFLAGS) $(OBJS) -o $@

vpoly_to_hpoly : $(OBJS) vpoly_to_hpoly.cpp
	$(CC) $@.cpp $(CPPFLAGS) $(OBJS) -o $@

hpoly_to_vpoly : $(OBJS) hpoly_to_vpoly.cpp
	$(CC) $@.cpp $(CPPFLAGS) $(OBJS) -o $@

clean:
	rm $(OBJS)
