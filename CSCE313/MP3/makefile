CC=g++ -g --std=c++11

all: dataserver client fifo

%.o: %.C %.H
	$(CC) -o $@ -c $<

dataserver: dataserver.C reqchannel.o
	$(CC) -g -o $@ dataserver.C reqchannel.o -lpthread

client: client.C client.H semaphore.o bounded_buffer.o reqchannel.o
	$(CC) -g -o $@ client.C semaphore.o bounded_buffer.o reqchannel.o -lpthread

fifo:
	rm -rf fifo*

clean: fifo
	rm -rf client dataserver reqchannel.o bounded_buffer.o semaphore.o *.dSYM/
