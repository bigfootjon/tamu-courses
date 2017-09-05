run: main out
	./out/main

main: main.o out
	g++ -o out/main out/main.o

main.o: main.cpp main.h out
	g++ -c main.cpp -o out/main.o

out:
	mkdir -p out

clean:
	rm -rf out/*
