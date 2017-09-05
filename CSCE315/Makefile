run: main out
	./out/main

gdb: main out
	gdb ./out/main

main: main.o out
	g++ --std=c++11 -g -o out/main out/main.o

main.o: main.cpp main.h out
	g++ --std=c++11 -g -c main.cpp -o out/main.o

out:
	mkdir -p out

clean:
	rm -rf out/*
