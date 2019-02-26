all: a.out

a.out: sem.cpp
	g++ -Igsl/include -Lgsl/lib  sem.cpp -lgsl -lblas

run:
	LD_LIBRARY_PATH=gsl/lib ./a.out