LDFLAGS=-ljsoncpp

debug:
	g++ -g3 -pg -o test test.cpp $(LDFLAGS)