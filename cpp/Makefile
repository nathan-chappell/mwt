CC = g++ -std=c++14
CPPFLAGS = -g -Og -Wall -Iinclude
OBJS_ = main polyhedra fourier_motzkin linear_algebra
OBJS = $(OBJS_:%=src/%.o)

main : $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@

clean:
	rm $(OBJS)
