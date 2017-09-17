CC=g++ --std=c++11 -g
CPP_FILES=$(wildcard *.cpp)
OBJ_FILES=$(addprefix out/,$(notdir $(CPP_FILES:.cpp=.o)))

run: out/main out
	./out/main <ta.txt

gdb: out/main out
	gdb ./out/main

out/main: $(OBJ_FILES) out
	$(CC) -o out/main $(OBJ_FILES)

out/%.o: %.cpp %.h out
	$(CC) -c $< -o $@

out:
	mkdir -p out

clean:
	rm -rf out
