all: out/dataserver out/simpleclient

out:
	mkdir out

out/%.o: %.C %.H out
	g++ -g -o $@ -c $<

out/dataserver: dataserver.C out/reqchannel.o out
	g++ -g -o $@ dataserver.C out/reqchannel.o -lpthread

out/simpleclient: simpleclient.C out/reqchannel.o out
	g++ -g -o $@ simpleclient.C out/reqchannel.o

clean:
	rm -rf out/
