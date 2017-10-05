# makefile

all: dataserver simpleclient

reqchannel.o: reqchannel.h reqchannel.c
	g++ -c -g reqchannel.c

dataserver: dataserver.c reqchannel.o 
	g++ -o dataserver dataserver.c reqchannel.o -lpthread

simpleclient: simpleclient.c reqchannel.o
	g++ -o simpleclient simpleclient.c reqchannel.o

clean:
	rm -f *.o simpleclient dataserver
