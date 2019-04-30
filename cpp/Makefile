CC = g++ -std=c++14
CPPFLAGS = -g -Og -Wall -Iinclude
OBJS_ = polyhedra fourier_motzkin linear_algebra 
OBJS = $(OBJS_:%=src/%.o)

all : main test/test

main : src/main.o $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@

test/test : test/test_functions.o test/test.o $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@

clean:
	rm $(OBJS)
	rm test/*.o
