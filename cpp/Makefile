CC = g++ -std=c++14
CPPFLAGS = -g -Og -Wall -Iinclude
OBJS_ = polyhedra fourier_motzkin linear_algebra 
OBJS = $(OBJS_:%=src/%.o)

all : main test

main : src/main.o $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@

test : testing/test_functions.o testing/test.o $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) src/main.o
	rm -f testing/*.o
