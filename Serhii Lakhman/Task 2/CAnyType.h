#pragma once
#include <typeinfo>
#include <ostream>
#include "MyException.h"

using namespace std;

template <class T>
class CAnyType
{

public:

	CAnyType();
	CAnyType(T Varible);
	CAnyType(const CAnyType<T>& other);

	~CAnyType();
	
	template <class T1>
	static bool IsCorrectType(CAnyType<T>& FirstObject, CAnyType<T1>& SecondObject);
	void static MySwap( CAnyType<T>& FirstObject,  CAnyType<T>& SecondObject);
		
	template <class T1>
	friend ostream& operator << (ostream& output, const CAnyType<T1>& Varible);
	CAnyType<T>& operator =(const CAnyType<T>& other);
	CAnyType<T>& operator=(T const Variable);

	void destroy();
	string GetType();
	
	bool			to_bool();
	char			to_char();
	int				to_int();
	float			to_float();
	double			to_double();
	unsigned int	to_unsignet_int();


private: 

	T *Variable;
	string TypeName;

};

#include "CAnyType.inl"
