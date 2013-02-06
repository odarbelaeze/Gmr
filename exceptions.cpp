#include <exception>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class BadJsonFile: public exception
{
	const string reason;
public:
	BadJsonFile(): reason("Unknown.") {}
	BadJsonFile(const string _reason): reason(_reason) {}
	virtual ~BadJsonFile() throw() {}

	virtual const char* what() const throw() 
	{
		return ("Your json file was bad configured because: " + reason).data();
	}
};

int main(int argc, char const *argv[])
{
	try{
		throw BadJsonFile("Your json file was bad configured.");
	}
	catch (BadJsonFile bjs) {
		cout << bjs.what() << endl;
		return 1;
	}
	
	return 0;
}