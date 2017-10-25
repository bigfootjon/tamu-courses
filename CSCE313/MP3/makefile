CC=g++ -g --std=c++11

all: dataserver client

%.o: %.C %.H
	$(CC) -o $@ -c $<

dataserver: dataserver.C reqchannel.o
	$(CC) -g -o $@ dataserver.C reqchannel.o -lpthread

client: client.C client.H semaphore.o bounded_buffer.o reqchannel.o
	$(CC) -g -o $@ client.C semaphore.o bounded_buffer.o reqchannel.o -lpthread

clean:
	rm -rf client dataserver reqchannel.o bounded_buffer.o semaphore.o fifo*
