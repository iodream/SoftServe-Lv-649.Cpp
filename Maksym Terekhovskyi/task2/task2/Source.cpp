#include "AnyType.h"
using namespace std;

int main(){
	AnyType a = 150;
	AnyType b = 'g';
	AnyType c = (float)1.4;
	
	float fc = c.GetFloatVal();
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


	/*int choice = 0;
	switch (choice)
	{
	case 1: 
		int qq = 8;
		cout << qq;
	default:
		break;
	}*/

	return 0;
}