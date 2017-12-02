CC=g++ -g --std=c++11

all: dataserver client

%.o: %.C %.H
	$(CC) -o $@ -c $<

dataserver: dataserver.C netreqchannel.o
	$(CC) -g -o $@ dataserver.C netreqchannel.o -lpthread

client: client.C client.H semaphore.o bounded_buffer.o netreqchannel.o
	$(CC) -g -o $@ client.C semaphore.o bounded_buffer.o netreqchannel.o -lpthread

clean:
	rm -rf client dataserver netreqchannel.o bounded_buffer.o semaphore.o *.dSYM/
