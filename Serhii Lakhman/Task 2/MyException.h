#pragma once
#include <iostream>

class MyExceptoin : public std::exception
{

public:
	
	MyExceptoin(const char *msg):exception(msg)
	{
		std::cout << "Something go wrong, when you try cast " << msg  << " to another type of data" << std::endl;
	}


};