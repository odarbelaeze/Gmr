LDFLAGS=-ljsoncpp

debug:
	g++ -c -O3 GMR.cpp
	g++ -g3 -pg -o test test.cpp $(LDFLAGS)

clean:
	rm GMR.o test