CC=g++ --std=c++11 -g

run: out/main out
	./out/main <input.txt

gdb: out/main out
	gdb ./out/main

out/main: out/main.o out/book.o out/course.o out
	$(CC) -o out/main out/main.o out/book.o out/course.o

out/main.o: main.cpp main.h out
	$(CC) -c main.cpp -o out/main.o

out/book.o: book.cpp book.h out
	$(CC) -c book.cpp -o out/book.o

out/course.o: course.cpp course.h out
	$(CC) -c course.cpp -o out/course.o

out:
	mkdir -p out

clean:
	rm -rf out
