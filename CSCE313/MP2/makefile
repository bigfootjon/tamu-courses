CC=g++

all: client dataserver mutex.o mutex_guard.o semaphore.o

reqchannel.o: reqchannel.H reqchannel.C
	$(CC) -c reqchannel.C

dataserver.o: dataserver.C
	$(CC) -c dataserver.C

client.o: client.C
	$(CC) -c client.C

mutex.o: mutex.C mutex.H
	$(CC) -c mutex.C

mutex_guard.o: mutex_guard.C mutex_guard.H
	$(CC) -c mutex_guard.C

semaphore.o: semaphore.C semaphore.H
	$(CC) -c semaphore.C

client: client.o reqchannel.o
	$(CC) -o client client.o reqchannel.o -lpthread

dataserver: dataserver.o reqchannel.o
	$(CC) -o dataserver dataserver.o reqchannel.o

clean:
	rm -f *.o client dataserver
