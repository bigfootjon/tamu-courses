all: out/memtest out/test

run: out/test out
	./out/test

out/my_allocator.o: my_allocator.c my_allocator.h out
	gcc -c -g my_allocator.c -o ./out/my_allocator.o

out/memtest: memtest.c out/my_allocator.o out
	gcc -o ./out/memtest memtest.c ./out/my_allocator.o

out/test: test.c out/my_allocator.o out
	gcc -o ./out/test test.c ./out/my_allocator.o

out:
	mkdir -p out

clean:
	rm -rf out
