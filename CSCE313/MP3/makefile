CC=g++ -g --std=c++11

all: out/dataserver out/client

out:
	mkdir out

out/%.o: %.C %.H out
	$(CC) -o $@ -c $<

out/dataserver: dataserver.C out/reqchannel.o out
	$(CC) -g -o $@ dataserver.C out/reqchannel.o -lpthread

out/client: client.C client.H out/semaphore.o out/bounded_buffer.o out/reqchannel.o out
	$(CC) -g -o $@ client.C out/semaphore.o out/bounded_buffer.o out/reqchannel.o

clean:
	rm -rf out/
