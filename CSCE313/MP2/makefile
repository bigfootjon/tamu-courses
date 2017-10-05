CC=g++

all: client mutex.o mutex_guard.o

reqchannel.o: reqchannel.h reqchannel.cpp
	$(CC) -c reqchannel.cpp

dataserver.o: dataserver.cpp dataserver.h
	$(CC) -c dataserver.cpp

client.o: client.cpp
	$(CC) -c client.cpp

mutex.o: mutex.cpp mutex.h
	$(CC) -c mutex.cpp

mutex_guard.o: mutex_guard.cpp mutex_guard.h
	$(CC) -c mutex_guard.cpp

client: client.o reqchannel.o dataserver.o
	$(CC) -o client client.o reqchannel.o dataserver.o -lpthread

clean:
	rm -f *.o client
