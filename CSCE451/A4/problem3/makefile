CC=gcc
CFLAGS=-m32 -g -no-pie -Wl,--build-id=sha1

assignment4rebuild: kaboom.o yellow_preflight.o yellow.o blue_preflight.o blue.o green_preflight.o green.o red_preflight.o red.o postred.o main.o postred.o menu.o disarm_handler.o libc_start_main.o gettimeleft.o
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	rm -rf *.o assignment4rebuild

%.o: %.c include.h
	$(CC) $(CFLAGS) -o $@ -c $<
