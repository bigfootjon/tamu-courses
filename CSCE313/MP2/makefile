CC=g++

main: client dataserver

all: main mutex.o mutex_guard.o semaphore.o

client: client.C reqchannel.o
	$(CC) -o client client.C reqchannel.o -lpthread

dataserver: dataserver.C reqchannel.o
	$(CC) -o dataserver dataserver.C reqchannel.o -lpthread

reqchannel.o: reqchannel.H reqchannel.C
	$(CC) -c reqchannel.C

mutex.o: mutex.C mutex.H
	$(CC) -c mutex.C

mutex_guard.o: mutex_guard.C mutex_guard.H
	$(CC) -c mutex_guard.C

semaphore.o: semaphore.C semaphore.H
	$(CC) -c semaphore.C

clean:
	rm -f *.o client dataserver
