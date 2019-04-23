CC = g++ -std=c++14
CPPFLAGS = -g -Og -Wall
OBJS = fourier_motzkin.o common.o

vcone_to_hcone : $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) $@.cpp -o $@

