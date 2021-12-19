#include "AnyType.hpp"
#include <iostream>


int main() {
	AnyType value = 1;
	value = true;
	value = 1.7;

	try {
		int tempInt = value.ToInt();
	}
	catch (const char *msg) {
		std::cerr << msg;
	}

	double tempDouble = value.ToDouble();
	return 0;
}
