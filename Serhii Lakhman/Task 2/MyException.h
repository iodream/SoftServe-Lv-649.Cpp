#pragma once
#include <iostream>

class MyExceptoin : public std::exception
{

public:
	
	MyExceptoin(const char *msg):exception(msg)
	{

		std::cout << "!!! CAnyType exception !!!" << std::endl;
		std::cout << "The variable that you want cast is not ";
	}


};