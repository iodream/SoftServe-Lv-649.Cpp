#include "CAnyType.h"


template<class T>
inline CAnyType<T>::CAnyType()
{
	this->Variable = nullptr;
}



template<class T>
inline CAnyType<T>::CAnyType(T varible)
{

	this->Variable = new T;

	*(this->Variable) = varible;
	
	TypeName = typeid(varible).name();

}



template<class T>
inline CAnyType<T>::CAnyType(const CAnyType<T>& other)
{
	destroy();

	 this->Variable = new T;

	*(this->Variable) = *(other.Variable);

}



template<class T>
inline CAnyType<T>::~CAnyType()
{
	destroy();
}




template<class T>
inline void CAnyType<T>::destroy()
{
	delete this->Variable;

	this->Variable = nullptr;
}



template<class T>
inline void CAnyType<T>::MySwap(CAnyType<T>& FirstObject, CAnyType<T>& SecondObject)
{
	CAnyType<T> temp = move(FirstObject);
	FirstObject = move(SecondObject);
	SecondObject = move(temp);

}




template<class T>
inline string CAnyType<T>::GetType()
{
	return this->TypeName;
}




template<class T>
inline CAnyType<T>& CAnyType<T>::operator=(const CAnyType<T>& other)
{
	
	if (this == &other)			return *this;
	
	destroy();

	this->Variable = new T;

	*(this->Variable) = *(other.Variable);

	return *this;

}



template<class T1>
inline ostream& operator<<(ostream& output, const CAnyType<T1>& Varible)
{

	output << *(Varible.Variable);

	return output;

}



template<class T>
inline CAnyType<T>& CAnyType<T>::operator=(T const Variable)
{

		destroy();

		this->Variable = new T;

		*(this->Variable) = Variable;

		return *this;
	
}




template<class T>
template<class T1>
inline bool CAnyType<T>::IsCorrectType(CAnyType<T>& FirstObject, CAnyType<T1>& SecondObject)
{
	return FirstObject.GetType() == SecondObject.GetType();
}




template<class T>
inline bool CAnyType<T>::to_bool()
{
	if (this->GetType() != typeid(bool).name())
		throw MyExceptoin("bool");

	return *(this->Variable);
}




template<class T>
inline char CAnyType<T>::to_char()
{
	if (this->GetType() != typeid(char).name())
		throw MyExceptoin("char");

	return *(this->Variable);
}




template<class T>
inline int CAnyType<T>::to_int()
{
	if (this->GetType() != typeid(int).name())
		throw MyExceptoin("int");

	return *(this->Variable);
}




template<class T>
inline float CAnyType<T>::to_float()
{
	if (this->GetType() != typeid(float).name())
		throw MyExceptoin("float");

	return *(this->Variable);
}




template<class T>
inline double CAnyType<T>::to_double()
{
	if (this->GetType() != typeid(double).name())
		throw MyExceptoin("double");

	return *(this->Variable);
}




template<class T>
inline unsigned int CAnyType<T>::to_unsignet_int()
{
	if (this->GetType() != typeid(unsigned int).name())
		throw MyExceptoin("unsigned int");

	return *(this->Variable);
}



