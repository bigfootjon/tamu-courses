p3: p3.S
	gcc -c p3.S -o p3.o
	gcc -o p3 p3.o

p2: p2.S
	gcc -c p2.S -o p2.o
	gcc -o p2 p2.o

p1: p1.S
	gcc -c p1.S -o p1.o
	gcc -o p1 p1.o

bonus: bonus.S
	gcc -c bonus.S -o bonus.o
	gcc -o bonus bonus.o

clean:
	rm -f *.o p1 p2 p3 bonus
