LDFLAGS=-ljsoncpp

debug:
	g++ -c -O3 gmr.cpp
	g++ -g3 -pg -o test test.cpp gmr.o $(LDFLAGS)

clean:
	rm GMR.o test