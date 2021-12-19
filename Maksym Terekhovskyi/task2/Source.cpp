#include "AnyType.h"
using namespace std;

int main(){
	AnyType a = 150;
	AnyType b = 'g';
	AnyType c = (float)1.4;
	c = 0;
	
	float fc = c.GetIntVal();
	cout << fc << endl;

	//AnyType at = 74;
	try {
		c %= (float)4.6;
		cout << c.GetIntVal();
	}
	catch(InvalidTypeException & ite){
		cout << ite.what();
	}
	catch (exception& ex) {
		cout << ex.what();
	}
	catch (...) {
		cout << "unknown exception caught\n";
	}



	return 0;
}