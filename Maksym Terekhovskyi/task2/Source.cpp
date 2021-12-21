#include "AnyType.h"
using namespace std;

int main(){
	AnyType a = 150;
	AnyType b = 3;
	a = 75.4;

	a.Swap(b);
	a.Print();

	try {
		a += b;
	}
	catch (InvalidTypeException& itex) {
		cout << itex.what() << endl;
	}
	catch (...) {
		cout << "unhandled exception caught\n";
	}


	return 0;
}