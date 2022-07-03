all: string_invert fork_fac

run: all
	./string_invert testme
	./fork_fac 7

fork_fac: fork_fac.c
	gcc -g fork_fac.c -o fork_fac

string_invert: string_invert.c
	gcc -g string_invert.c -o string_invert

clean:
	rm -f string_invert fork_fac
