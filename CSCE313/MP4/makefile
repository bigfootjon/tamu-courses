CC=g++ -g --std=c++11

all: dataserver client

%.o: %.C %.H
	$(CC) -o $@ -c $<

dataserver: dataserver.C reqchannel.o 
	$(CC) -o dataserver dataserver.C reqchannel.o -lpthread

client: client.C reqchannel.o bounded_buffer.o semaphore.o
	$(CC) -o $@ $^

clean:
	rm -rf *.o client dataserver *.dSYM
