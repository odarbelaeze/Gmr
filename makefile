LDFLAGS=-ljsoncpp

debug:
	g++ -c -O3 gmr.cpp
	g++ -g3 -pg -o main main.cpp gmr.o $(LDFLAGS)

test:
	g++ -o tests/bin/sc tests/sc.cpp
	g++ -o tests/bin/bcc tests/bcc.cpp
	g++ -o tests/bin/fcc tests/fcc.cpp
	g++ -o tests/bin/pbc tests/pbc.cpp gmr.o $(LDFLAGS)
	g++ -o tests/bin/test tests/test.cpp gmr.o $(LDFLAGS)



clean:
	rm GMR.o test