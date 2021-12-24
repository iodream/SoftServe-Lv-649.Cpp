#pragma once
#include <iostream>
using namespace std;

class InvalidTypeException : public exception {
public:
	string msg;
	InvalidTypeException(string msg) {
		this->msg = msg;
	}
	string what() {
		return "Exception caught: " + msg;
	}
};

class AnyType
{
public:
	// Possible value types of an AST node.
	enum class ValueType
	{
		BOOLEAN, INTEGER, CHAR, FLOAT, DOUBLE, UNSIGNED_INT, SHORT_INT, UNSIGNED_SHORT_INT, LONG_INT, UNSIGNED_LONG_INT, LONG_LONG_INT, UNSIGNED_LONG_LONG_INT, UNKNOWN
	};

public:	// Constructors
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

public:	// Value accessors
	bool GetBoolVal() const{
		if (mType != ValueType::BOOLEAN) {
			throw InvalidTypeException("Your type is not 'bool'");
		}
		return boolVal;
	}

	int GetIntVal() const{
		if (mType != ValueType::INTEGER) {
			throw InvalidTypeException("Your type is not 'int'");
		}
		return intVal;
	}

	char GetCharVal() const{
		if (mType != ValueType::CHAR) {
			throw InvalidTypeException("Your type is not 'char'");
		}
		return charVal;
	}

	float GetFloatVal() const{
		if (mType != ValueType::FLOAT) {
			throw InvalidTypeException("Your type is not 'float'");
		}
		return floatVal;
	}

	double GetDoubleVal() const{
		if (mType != ValueType::DOUBLE) {
			throw InvalidTypeException("Your type is not 'double'");
		}
		return doubleVal;
	}

	unsigned int GetUintVal() const {
		if (mType != ValueType::UNSIGNED_INT) {
			throw InvalidTypeException("Your type is not 'unsigned int'");
		}
		return uintVal;
	}

	short int GetSintVal() const {
		if (mType != ValueType::SHORT_INT) {
			throw InvalidTypeException("Your type is not 'short int'");
		}
		return sintVal;
	}

	long int GetLintVal() const {
		if (mType != ValueType::LONG_INT) {
			throw InvalidTypeException("Your type is not 'long int'");
		}
		return lintVal;
	}

	unsigned short int GetUsintVal() const {
		if (mType != ValueType::UNSIGNED_SHORT_INT) {
			throw InvalidTypeException("Your type is not 'unsigned short int'");
		}
		return usintVal;
	}

	unsigned long int GetUlintVal() const {
		if (mType != ValueType::UNSIGNED_LONG_INT) {
			throw InvalidTypeException("Your type is not 'unsigned long int'");
		}
		return ulintVal;
	}

	unsigned long long int GetLlintVal() const {
		if (mType != ValueType::LONG_LONG_INT) {
			throw InvalidTypeException("Your type is not 'long long int'");
		}
		return llintVal;
	}

	unsigned long long int GetUllintVal() const {
		if (mType != ValueType::UNSIGNED_LONG_LONG_INT) {
			throw InvalidTypeException("Your type is not 'unsigned long long int'");
		}
		return ullintVal;
	}

	void Print(){
		switch (mType)
		{
		case ValueType::BOOLEAN:
			cout << (bool)boolVal << endl;
			break;
		case ValueType::INTEGER:
			cout << intVal << endl;
			break;
		case ValueType::CHAR:
			cout << (char)charVal << endl;
			break;
		case ValueType::FLOAT:
			cout << floatVal << endl;
			break;
		case ValueType::DOUBLE:
			cout << doubleVal << endl;
			break;
		case ValueType::UNSIGNED_INT:
			cout << uintVal << endl;
			break;
		case ValueType::SHORT_INT:
			cout << sintVal << endl;
			break;
		case ValueType::LONG_INT:
			cout << lintVal << endl;
			break;
		case ValueType::UNSIGNED_SHORT_INT:
			cout << usintVal << endl;
			break;
		case ValueType::UNSIGNED_LONG_INT:
			cout << ulintVal << endl;
			break;
		case ValueType::LONG_LONG_INT:
			cout << llintVal << endl;
			break;
		case ValueType::UNSIGNED_LONG_LONG_INT:
			cout << ullintVal << endl;
			break;
		default:
			throw std::runtime_error("unknown type");
		}
	}

	AnyType& operator=(const AnyType& other){
		this->~AnyType();
		new(this) AnyType(other);
		return *this;
	}

	AnyType& operator+=(const AnyType& other) {
		switch (mType) {
		case ValueType::BOOLEAN: {
			bool Value1 = GetBoolVal(), Value2 = other.GetBoolVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::INTEGER: {
			int Value1 = GetIntVal(), Value2 = other.GetIntVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::CHAR: {
			char Value1 = GetCharVal(), Value2 = other.GetCharVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::FLOAT: {
			float Value1 = GetFloatVal(), Value2 = other.GetFloatVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::DOUBLE: {
			double Value1 = GetDoubleVal(), Value2 = other.GetDoubleVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_INT: {
			unsigned int Value1 = GetUintVal(), Value2 = other.GetUintVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::SHORT_INT: {
			short int Value1 = GetSintVal(), Value2 = other.GetSintVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::LONG_INT: {
			long int Value1 = GetLintVal(), Value2 = other.GetLintVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_SHORT_INT: {
			unsigned short int Value1 = GetUsintVal(), Value2 = other.GetUsintVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_LONG_INT: {
			unsigned long int Value1 = GetUlintVal(), Value2 = other.GetUlintVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::LONG_LONG_INT: {
			long long int Value1 = GetLlintVal(), Value2 = other.GetLlintVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_LONG_LONG_INT: {
			unsigned long long int Value1 = GetUllintVal(), Value2 = other.GetUllintVal();
			this->~AnyType();
			new(this) AnyType(Value1 + Value2);
			return *this;
			break;
		}
		default:
			throw InvalidTypeException("this type is not supported yet");
			break;
		}
	}

	AnyType& operator-=(const AnyType& other) {
		switch (mType) {
		case ValueType::BOOLEAN: {
			bool Value1 = GetBoolVal(), Value2 = other.GetBoolVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::INTEGER: {
			int Value1 = GetIntVal(), Value2 = other.GetIntVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::CHAR: {
			char Value1 = GetCharVal(), Value2 = other.GetCharVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::FLOAT: {
			float Value1 = GetFloatVal(), Value2 = other.GetFloatVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::DOUBLE: {
			double Value1 = GetDoubleVal(), Value2 = other.GetDoubleVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_INT: {
			unsigned int Value1 = GetUintVal(), Value2 = other.GetUintVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::SHORT_INT: {
			short int Value1 = GetSintVal(), Value2 = other.GetSintVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::LONG_INT: {
			long int Value1 = GetLintVal(), Value2 = other.GetLintVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_SHORT_INT: {
			unsigned short int Value1 = GetUsintVal(), Value2 = other.GetUsintVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_LONG_INT: {
			unsigned long int Value1 = GetUlintVal(), Value2 = other.GetUlintVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::LONG_LONG_INT: {
			long long int Value1 = GetLlintVal(), Value2 = other.GetLlintVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_LONG_LONG_INT: {
			unsigned long long int Value1 = GetUllintVal(), Value2 = other.GetUllintVal();
			this->~AnyType();
			new(this) AnyType(Value1 - Value2);
			return *this;
			break;
		}
		default:
			throw InvalidTypeException("this type is not supported yet");
			break;
		}
	}

	AnyType& operator*=(const AnyType& other) {
		switch (mType) {
		case ValueType::BOOLEAN: {
			bool Value1 = GetBoolVal(), Value2 = other.GetBoolVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::INTEGER: {
			int Value1 = GetIntVal(), Value2 = other.GetIntVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::CHAR: {
			char Value1 = GetCharVal(), Value2 = other.GetCharVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::FLOAT: {
			float Value1 = GetFloatVal(), Value2 = other.GetFloatVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::DOUBLE: {
			double Value1 = GetDoubleVal(), Value2 = other.GetDoubleVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_INT: {
			unsigned int Value1 = GetUintVal(), Value2 = other.GetUintVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::SHORT_INT: {
			short int Value1 = GetSintVal(), Value2 = other.GetSintVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::LONG_INT: {
			long int Value1 = GetLintVal(), Value2 = other.GetLintVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_SHORT_INT: {
			unsigned short int Value1 = GetUsintVal(), Value2 = other.GetUsintVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_LONG_INT: {
			unsigned long int Value1 = GetUlintVal(), Value2 = other.GetUlintVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::LONG_LONG_INT: {
			long long int Value1 = GetLlintVal(), Value2 = other.GetLlintVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_LONG_LONG_INT: {
			unsigned long long int Value1 = GetUllintVal(), Value2 = other.GetUllintVal();
			this->~AnyType();
			new(this) AnyType(Value1 * Value2);
			return *this;
			break;
		}
		default:
			throw InvalidTypeException("this type is not supported yet");
			break;
		}
	}

	AnyType& operator/=(const AnyType& other) {
		switch (mType) {
		case ValueType::BOOLEAN: {
			bool Value1 = GetBoolVal(), Value2 = other.GetBoolVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::INTEGER: {
			int Value1 = GetIntVal(), Value2 = other.GetIntVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::CHAR: {
			char Value1 = GetCharVal(), Value2 = other.GetCharVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::FLOAT: {
			float Value1 = GetFloatVal(), Value2 = other.GetFloatVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::DOUBLE: {
			double Value1 = GetDoubleVal(), Value2 = other.GetDoubleVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_INT: {
			unsigned int Value1 = GetUintVal(), Value2 = other.GetUintVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::SHORT_INT: {
			short int Value1 = GetSintVal(), Value2 = other.GetSintVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::LONG_INT: {
			long int Value1 = GetLintVal(), Value2 = other.GetLintVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_SHORT_INT: {
			unsigned short int Value1 = GetUsintVal(), Value2 = other.GetUsintVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_LONG_INT: {
			unsigned long int Value1 = GetUlintVal(), Value2 = other.GetUlintVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::LONG_LONG_INT: {
			long long int Value1 = GetLlintVal(), Value2 = other.GetLlintVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_LONG_LONG_INT: {
			unsigned long long int Value1 = GetUllintVal(), Value2 = other.GetUllintVal();
			this->~AnyType();
			new(this) AnyType(Value1 / Value2);
			return *this;
			break;
		}
		default:
			throw InvalidTypeException("this type is not supported yet");
			break;
		}
	}

	AnyType& operator%=(const AnyType& other) {
		switch (mType) {
		case ValueType::BOOLEAN: {
			bool Value1 = GetBoolVal(), Value2 = other.GetBoolVal();
			this->~AnyType();
			new(this) AnyType(Value1 % Value2);
			return *this;
			break;
		}
		case ValueType::INTEGER: {
			int Value1 = GetIntVal(), Value2 = other.GetIntVal();
			this->~AnyType();
			new(this) AnyType(Value1 % Value2);
			return *this;
			break;
		}
		case ValueType::CHAR: {
			char Value1 = GetCharVal(), Value2 = other.GetCharVal();
			this->~AnyType();
			new(this) AnyType(Value1 % Value2);
			return *this;
			break;
		}
		case ValueType::FLOAT: {
			cout << "cannot take remainder from division of two values of type 'float', returning the remainder from 'int' type division;\n";
			float Value1 = GetFloatVal(), Value2 = other.GetFloatVal();
			this->~AnyType();
			new(this) AnyType((int)Value1 % (int)Value2);
			return *this;
			break;
		}
		case ValueType::DOUBLE: {
			cout << "cannot take remainder from division of two values of type 'double', returning the remainder from 'int' type division;\n";
			double Value1 = GetDoubleVal(), Value2 = other.GetDoubleVal();
			this->~AnyType();
			new(this) AnyType((int)Value1 % (int)Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_INT: {
			unsigned int Value1 = GetUintVal(), Value2 = other.GetUintVal();
			this->~AnyType();
			new(this) AnyType(Value1 % Value2);
			return *this;
			break;
		}
		case ValueType::SHORT_INT: {
			short int Value1 = GetSintVal(), Value2 = other.GetSintVal();
			this->~AnyType();
			new(this) AnyType(Value1 % Value2);
			return *this;
			break;
		}
		case ValueType::LONG_INT: {
			long int Value1 = GetLintVal(), Value2 = other.GetLintVal();
			this->~AnyType();
			new(this) AnyType(Value1 % Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_SHORT_INT: {
			unsigned short int Value1 = GetUsintVal(), Value2 = other.GetUsintVal();
			this->~AnyType();
			new(this) AnyType(Value1 % Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_LONG_INT: {
			unsigned long int Value1 = GetUlintVal(), Value2 = other.GetUlintVal();
			this->~AnyType();
			new(this) AnyType(Value1 % Value2);
			return *this;
			break;
		}
		case ValueType::LONG_LONG_INT: {
			long long int Value1 = GetLlintVal(), Value2 = other.GetLlintVal();
			this->~AnyType();
			new(this) AnyType(Value1 % Value2);
			return *this;
			break;
		}
		case ValueType::UNSIGNED_LONG_LONG_INT: {
			unsigned long long int Value1 = GetUllintVal(), Value2 = other.GetUllintVal();
			this->~AnyType();
			new(this) AnyType(Value1 % Value2);
			return *this;
			break;
		}
		default:
			throw InvalidTypeException("this type is not supported yet");
			break;
		}
	}

	~AnyType(){
		switch (mType)
		{
		case ValueType::BOOLEAN:
			boolVal = false;
			break;
		case ValueType::INTEGER:
			intVal = 0;
			break;
		case ValueType::CHAR:
			charVal = '\0';
			break;
		case ValueType::FLOAT:
			floatVal = 0;
			break;
		case ValueType::DOUBLE:
			doubleVal = 0;
			break;
		case ValueType::UNSIGNED_INT:
			uintVal = 0;
			break;
		case ValueType::SHORT_INT:
			sintVal = 0;
			break;
		case ValueType::LONG_INT:
			lintVal = 0;
			break;
		case ValueType::UNSIGNED_SHORT_INT:
			usintVal = 0;
			break;
		case ValueType::UNSIGNED_LONG_INT:
			ulintVal = 0;
			break;
		case ValueType::LONG_LONG_INT:
			llintVal = 0;
			break;
		case ValueType::UNSIGNED_LONG_LONG_INT:
			ullintVal = 0;
			break;
		default:
			throw std::runtime_error("unknown type");
		}
	}

	void Swap(AnyType& other) {
		AnyType temp = other;
		other = *this;
		*this = temp; 
	}

private:
	ValueType mType;	// Type of the AnyType
	union{
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