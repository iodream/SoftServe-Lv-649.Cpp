#include "AnyType.h"

InvalidTypeException::InvalidTypeException(string msg) {
	this->msg = msg;
}
string InvalidTypeException::what() {
	return this->msg;
}

AnyType::~AnyType() {
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

bool AnyType::GetBoolVal() const {
	if (mType != ValueType::BOOLEAN) {
		throw InvalidTypeException("Your type is not 'bool'");
	}
	return boolVal;
}
int AnyType::GetIntVal() const {
	if (mType != ValueType::INTEGER) {
		throw InvalidTypeException("Your type is not 'int'");
	}
	return intVal;
}
char AnyType::GetCharVal() const {
	if (mType != ValueType::CHAR) {
		throw InvalidTypeException("Your type is not 'char'");
	}
	return charVal;
}
float AnyType::GetFloatVal() const {
	if (mType != ValueType::FLOAT) {
		throw InvalidTypeException("Your type is not 'float'");
	}
	return floatVal;
}
double AnyType::GetDoubleVal() const {
	if (mType != ValueType::DOUBLE) {
		throw InvalidTypeException("Your type is not 'double'");
	}
	return doubleVal;
}
unsigned int AnyType::GetUintVal() const {
	if (mType != ValueType::UNSIGNED_INT) {
		throw InvalidTypeException("Your type is not 'unsigned int'");
	}
	return uintVal;
}
short int AnyType::GetSintVal() const {
	if (mType != ValueType::SHORT_INT) {
		throw InvalidTypeException("Your type is not 'short int'");
	}
	return sintVal;
}
long int AnyType::GetLintVal() const {
	if (mType != ValueType::LONG_INT) {
		throw InvalidTypeException("Your type is not 'long int'");
	}
	return lintVal;
}
unsigned short int AnyType::GetUsintVal() const {
	if (mType != ValueType::UNSIGNED_SHORT_INT) {
		throw InvalidTypeException("Your type is not 'unsigned short int'");
	}
	return usintVal;
}
unsigned long int AnyType::GetUlintVal() const {
	if (mType != ValueType::UNSIGNED_LONG_INT) {
		throw InvalidTypeException("Your type is not 'unsigned long int'");
	}
	return ulintVal;
}
unsigned long long int AnyType::GetLlintVal() const {
	if (mType != ValueType::LONG_LONG_INT) {
		throw InvalidTypeException("Your type is not 'long long int'");
	}
	return llintVal;
}
unsigned long long int AnyType::GetUllintVal() const {
	if (mType != ValueType::UNSIGNED_LONG_LONG_INT) {
		throw InvalidTypeException("Your type is not 'unsigned long long int'");
	}
	return ullintVal;
}

void AnyType::Print() {
	switch (mType){
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
		cout << GetFloatVal() << endl;
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

AnyType& AnyType::operator=(const AnyType& other) {
	switch (other.mType){
	case ValueType::BOOLEAN:
		this->boolVal = other.GetBoolVal();		
		break;
	case ValueType::INTEGER:
		this->intVal = other.GetIntVal();
		break;
	case ValueType::CHAR:
		this->charVal = other.GetCharVal();
		break;
	case ValueType::FLOAT:
		this->floatVal = other.GetFloatVal();
		break;
	case ValueType::DOUBLE:
		this->doubleVal = other.GetDoubleVal();
		break;
	case ValueType::UNSIGNED_INT:
		this->uintVal = other.GetUintVal();
		break;
	case ValueType::SHORT_INT:
		this->sintVal = other.GetSintVal();
		break;
	case ValueType::LONG_INT:
		this->lintVal = other.GetLintVal();
		break;
	case ValueType::UNSIGNED_SHORT_INT:
		this->usintVal = other.GetUsintVal();
		break;
	case ValueType::UNSIGNED_LONG_INT:
		this->ulintVal = other.GetUlintVal();
		break;
	case ValueType::LONG_LONG_INT:
		this->llintVal = other.GetLlintVal();
		break;
	case ValueType::UNSIGNED_LONG_LONG_INT:
		this->ullintVal = other.GetUllintVal();
		break;
	default:
		break;
	}
	mType = other.mType;
	return *this;
}

AnyType& AnyType::operator+=(const AnyType& other) {
	if (mType == other.mType) {
		switch (mType) {
		case AnyType::ValueType::BOOLEAN:
			this->boolVal += other.GetBoolVal();
			break;
		case AnyType::ValueType::INTEGER:
			this->intVal += other.GetIntVal();
			break;
		case AnyType::ValueType::CHAR:
			this->charVal += other.GetCharVal();
			break;
		case AnyType::ValueType::FLOAT:
			this->floatVal += other.GetFloatVal();
			break;
		case AnyType::ValueType::DOUBLE:
			this->doubleVal += other.GetDoubleVal();
			break;
		case AnyType::ValueType::UNSIGNED_INT:
			this->uintVal += other.GetUintVal();
			break;
		case AnyType::ValueType::SHORT_INT:
			this->sintVal += other.GetSintVal();
			break;
		case AnyType::ValueType::UNSIGNED_SHORT_INT:
			this->usintVal += other.GetUsintVal();
			break;
		case AnyType::ValueType::LONG_INT:
			this->lintVal += other.GetLintVal();
			break;
		case AnyType::ValueType::UNSIGNED_LONG_INT:
			this->ulintVal += other.GetUlintVal();
			break;
		case AnyType::ValueType::LONG_LONG_INT:
			this->llintVal += other.GetLlintVal();
			break;
		case AnyType::ValueType::UNSIGNED_LONG_LONG_INT:
			this->ullintVal += other.GetUllintVal();
			break;
		case AnyType::ValueType::UNKNOWN:
			break;
		default:
			break;
		}
	}
	else {
		throw InvalidTypeException("your types do not match");
	}
	return *this;
}
AnyType& AnyType::operator-=(const AnyType& other) {
	if (mType == other.mType) {
		switch (mType) {
		case AnyType::ValueType::BOOLEAN:
			this->boolVal -= other.GetBoolVal();
			break;
		case AnyType::ValueType::INTEGER:
			this->intVal -= other.GetIntVal();
			break;
		case AnyType::ValueType::CHAR:
			this->charVal -= other.GetCharVal();
			break;
		case AnyType::ValueType::FLOAT:
			this->floatVal -= other.GetFloatVal();
			break;
		case AnyType::ValueType::DOUBLE:
			this->doubleVal -= other.GetDoubleVal();
			break;
		case AnyType::ValueType::UNSIGNED_INT:
			this->uintVal -= other.GetUintVal();
			break;
		case AnyType::ValueType::SHORT_INT:
			this->sintVal -= other.GetSintVal();
			break;
		case AnyType::ValueType::UNSIGNED_SHORT_INT:
			this->usintVal -= other.GetUsintVal();
			break;
		case AnyType::ValueType::LONG_INT:
			this->lintVal -= other.GetLintVal();
			break;
		case AnyType::ValueType::UNSIGNED_LONG_INT:
			this->ulintVal -= other.GetUlintVal();
			break;
		case AnyType::ValueType::LONG_LONG_INT:
			this->llintVal -= other.GetLlintVal();
			break;
		case AnyType::ValueType::UNSIGNED_LONG_LONG_INT:
			this->ullintVal -= other.GetUllintVal();
			break;
		case AnyType::ValueType::UNKNOWN:
			break;
		default:
			break;
		}
	}
	else {
		throw InvalidTypeException("your types do not match");
	}
	return *this;
}
AnyType& AnyType::operator*=(const AnyType& other) {
	if (mType == other.mType) {
		switch (mType) {
		case AnyType::ValueType::BOOLEAN:
			this->boolVal *= other.GetBoolVal();
			break;
		case AnyType::ValueType::INTEGER:
			this->intVal *= other.GetIntVal();
			break;
		case AnyType::ValueType::CHAR:
			this->charVal *= other.GetCharVal();
			break;
		case AnyType::ValueType::FLOAT:
			this->floatVal *= other.GetFloatVal();
			break;
		case AnyType::ValueType::DOUBLE:
			this->doubleVal *= other.GetDoubleVal();
			break;
		case AnyType::ValueType::UNSIGNED_INT:
			this->uintVal *= other.GetUintVal();
			break;
		case AnyType::ValueType::SHORT_INT:
			this->sintVal *= other.GetSintVal();
			break;
		case AnyType::ValueType::UNSIGNED_SHORT_INT:
			this->usintVal *= other.GetUsintVal();
			break;
		case AnyType::ValueType::LONG_INT:
			this->lintVal *= other.GetLintVal();
			break;
		case AnyType::ValueType::UNSIGNED_LONG_INT:
			this->ulintVal *= other.GetUlintVal();
			break;
		case AnyType::ValueType::LONG_LONG_INT:
			this->llintVal *= other.GetLlintVal();
			break;
		case AnyType::ValueType::UNSIGNED_LONG_LONG_INT:
			this->ullintVal *= other.GetUllintVal();
			break;
		case AnyType::ValueType::UNKNOWN:
			break;
		default:
			break;
		}
	}
	else {
		throw InvalidTypeException("your types do not match");
	}
	return *this;
}
AnyType& AnyType::operator/=(const AnyType& other) {
	if (mType == other.mType) {
		switch (mType) {
		case AnyType::ValueType::BOOLEAN:
			this->boolVal /= other.GetBoolVal();
			break;
		case AnyType::ValueType::INTEGER:
			this->intVal /= other.GetIntVal();
			break;
		case AnyType::ValueType::CHAR:
			this->charVal /= other.GetCharVal();
			break;
		case AnyType::ValueType::FLOAT:
			this->floatVal /= other.GetFloatVal();
			break;
		case AnyType::ValueType::DOUBLE:
			this->doubleVal /= other.GetDoubleVal();
			break;
		case AnyType::ValueType::UNSIGNED_INT:
			this->uintVal /= other.GetUintVal();
			break;
		case AnyType::ValueType::SHORT_INT:
			this->sintVal /= other.GetSintVal();
			break;
		case AnyType::ValueType::UNSIGNED_SHORT_INT:
			this->usintVal /= other.GetUsintVal();
			break;
		case AnyType::ValueType::LONG_INT:
			this->lintVal /= other.GetLintVal();
			break;
		case AnyType::ValueType::UNSIGNED_LONG_INT:
			this->ulintVal /= other.GetUlintVal();
			break;
		case AnyType::ValueType::LONG_LONG_INT:
			this->llintVal /= other.GetLlintVal();
			break;
		case AnyType::ValueType::UNSIGNED_LONG_LONG_INT:
			this->ullintVal /= other.GetUllintVal();
			break;
		case AnyType::ValueType::UNKNOWN:
			break;
		default:
			break;
		}
	}
	else {
		throw InvalidTypeException("your types do not match");
	}
	return *this;
}
AnyType& AnyType::operator%=(const AnyType& other) {
	if (mType == other.mType) {
		switch (mType) {
		case AnyType::ValueType::BOOLEAN:
			this->boolVal %= other.GetBoolVal();
			break;
		case AnyType::ValueType::INTEGER:
			this->intVal %= other.GetIntVal();
			break;
		case AnyType::ValueType::CHAR:
			this->charVal %= other.GetCharVal();
			break;
		case AnyType::ValueType::FLOAT:
			cout << "operation is impossible because the type of your operand is 'float'\n";
			break;
		case AnyType::ValueType::DOUBLE:
			cout << "operation is impossible because the type of your operand is 'double'\n";
			break;
		case AnyType::ValueType::UNSIGNED_INT:
			this->uintVal %= other.GetUintVal();
			break;
		case AnyType::ValueType::SHORT_INT:
			this->sintVal %= other.GetSintVal();
			break;
		case AnyType::ValueType::UNSIGNED_SHORT_INT:
			this->usintVal %= other.GetUsintVal();
			break;
		case AnyType::ValueType::LONG_INT:
			this->lintVal %= other.GetLintVal();
			break;
		case AnyType::ValueType::UNSIGNED_LONG_INT:
			this->ulintVal %= other.GetUlintVal();
			break;
		case AnyType::ValueType::LONG_LONG_INT:
			this->llintVal %= other.GetLlintVal();
			break;
		case AnyType::ValueType::UNSIGNED_LONG_LONG_INT:
			this->ullintVal %= other.GetUllintVal();
			break;
		case AnyType::ValueType::UNKNOWN:
			break;
		default:
			break;
		}
	}
	else {
		throw InvalidTypeException("your types do not match");
	}
	return *this;
}

void AnyType::Swap(AnyType& other) {
	AnyType temp = other;
	other = *this;
	*this = temp;
}