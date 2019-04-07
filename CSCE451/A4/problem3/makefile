# gcc 32bit x86 version 4.1.2

assignment4rebuild: kaboom.o yellow_preflight.o yellow.o blue_preflight.o blue.o green_preflight.o green.o red_preflight.o red.o postred.o main.o postred.o menu.o disarm_handler.o
	clang -o $@ $^

clean:
	rm -rf *.o assignment4rebuild

%.o: %.c include.h
	clang -o $@ -c $<
