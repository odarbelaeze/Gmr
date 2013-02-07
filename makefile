LDFLAGS=-ljsoncpp

debug:
	rm GMR.o test
	g++ -c -O3 GMR.cpp
	g++ -g3 -pg -o test test.cpp $(LDFLAGS)