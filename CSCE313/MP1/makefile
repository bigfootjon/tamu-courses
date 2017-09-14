all: out/memtest out/test

run: out/test out
	./out/test

out/%.o: %.c %.h out
	gcc -c -g $< -o $@

out/memtest: memtest.c out/my_allocator.o out/free_list.o out
	gcc -o ./out/memtest memtest.c ./out/my_allocator.o

out/test: test.c out/my_allocator.o out/free_list.o out
	gcc -o ./out/test test.c ./out/my_allocator.o

out:
	mkdir -p out

clean:
	rm -rf out
