#pragma once
#include <iostream>
using namespace std;

class InvalidTypeException : public exception {
public:
	string msg;
	InvalidTypeException(string msg);
	string what();
};

class AnyType {
public:
	enum class ValueType{
		BOOLEAN, INTEGER, CHAR, FLOAT, DOUBLE, UNSIGNED_INT, SHORT_INT, UNSIGNED_SHORT_INT, LONG_INT, UNSIGNED_LONG_INT, LONG_LONG_INT, UNSIGNED_LONG_LONG_INT, UNKNOWN
	};
	ValueType mType;
	// constructors
	AnyType() : mType{
		ValueType::UNKNOWN
	} {}
	AnyType(bool val) : mType{
		ValueType::BOOLEAN
	}, boolVal{
		val
	} {}
	AnyType(int val) : mType{
		ValueType::INTEGER
	}, intVal{
		val
	} {}
	AnyType(char val) : mType{
		ValueType::CHAR
	}, charVal{
		val
	} {}
	AnyType(float val) : mType{
		ValueType::FLOAT
	}, floatVal{
		val
	} {}
	AnyType(double val) : mType{
		ValueType::DOUBLE
	}, doubleVal{
		val
	} {}
	AnyType(unsigned int val) : mType{
		ValueType::UNSIGNED_INT
	}, uintVal{
		val
	} {}
	AnyType(short int val) : mType{
		ValueType::SHORT_INT
	}, sintVal{
		val
	} {}
	AnyType(long int val) : mType{
		ValueType::LONG_INT
	}, lintVal{
		val
	} {}
	AnyType(unsigned short int val) : mType{
		ValueType::UNSIGNED_SHORT_INT
	}, usintVal{
		val
	} {}
	AnyType(unsigned long int val) : mType{
		ValueType::UNSIGNED_LONG_INT
	}, ulintVal{
		val
	} {}
	AnyType(long long int val) : mType{
		ValueType::LONG_LONG_INT
	}, llintVal{
		val
	} {}
	AnyType(unsigned long long int val) : mType{
		ValueType::UNSIGNED_LONG_LONG_INT
	}, ullintVal{
		val
	} {}

	// GetType
	ValueType GetType() {
		return mType;
	}

	// GetValue
	bool GetBoolVal() const; 
	int GetIntVal() const;
	char GetCharVal() const;
	float GetFloatVal() const;
	double GetDoubleVal() const;
	unsigned int GetUintVal() const;
	short int GetSintVal() const;
	long int GetLintVal() const;
	unsigned short int GetUsintVal() const;
	unsigned long int GetUlintVal() const;
	unsigned long long int GetLlintVal() const;
	unsigned long long int GetUllintVal() const;

	// print
	void Print();

	// operators
	AnyType& operator=(const AnyType& other);
	AnyType& operator+=(const AnyType& other);
	AnyType& operator-=(const AnyType& other);
	AnyType& operator*=(const AnyType& other);
	AnyType& operator/=(const AnyType& other);
	AnyType& operator%=(const AnyType& other);

	// swap
	void Swap(AnyType& other);

	// destructor
	~AnyType();
private:	
	union {
		bool boolVal;
		int intVal;
		char charVal;
		float floatVal;
		double doubleVal;
		unsigned int uintVal;
		short int sintVal;
		long int lintVal;
		unsigned short int usintVal;
		unsigned long int ulintVal;
		long long int llintVal;
		unsigned long long int ullintVal;
	};
};