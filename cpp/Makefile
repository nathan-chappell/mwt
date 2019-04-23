CC = g++ -std=c++14
CPPFLAGS = -g -Og -Wall
OBJS = fourier_motzkin.o common.o

all : vcone_to_hcone hcone_to_vcone

vcone_to_hcone : $(OBJS) vcone_to_hcone.cpp
	$(CC) $(CPPFLAGS) $(OBJS) $@.cpp -o $@

hcone_to_vcone : $(OBJS) hcone_to_vcone.cpp
	$(CC) $(CPPFLAGS) $(OBJS) $@.cpp -o $@

