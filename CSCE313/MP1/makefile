all: out/memtest out/test

run: out/memtest out
	./out/memtest

out/%.o: %.c %.h out
	gcc --std=c99 -c -g $< -o $@

out/memtest: memtest.c out/my_allocator.o out/free_list.o out
	gcc --std=c99 -o ./out/memtest memtest.c ./out/my_allocator.o ./out/free_list.o

out/test: test.c out/my_allocator.o out/free_list.o out
	gcc --std=c99 -o ./out/test test.c ./out/my_allocator.o ./out/free_list.o

out:
	mkdir -p out

clean:
	rm -rf out
