#include "AnyType.hpp"

AnyType::AnyType() {
	type = "None";
}

void AnyType::Swap(AnyType& object) {
	AnyType temp;
	temp = object;
	object = *this;
	*this = temp;
}

std::string AnyType::GetType() {
	return type;
}

bool AnyType::ToBool() {
	if (type.compare("bool")) {
		throw "Bad cast exception!\n";
	}
	return DataBool;
};

char AnyType::ToChar() {
	if (type.compare("char")) {
		throw "Bad cast exception!\n";
	}
	return DataChar;
};

signed AnyType::ToSignedChar() {
	if (type.compare("signed char")) {
		throw "Bad cast exception!\n";
	}
	return DataSChar;
};

unsigned char AnyType::ToUnsignedChar() {
	if (type.compare("unsigned char")) {
		throw "Bad cast exception!\n";
	}
	return DataUnsChar;
};

wchar_t AnyType::ToWChar_T() {
	if (type.compare("wchar_t")) {
		throw "Bad cast exception!\n";
	}
	return DataWCharT;
};

char16_t AnyType::ToChar16_T() {
	if (type.compare("wchar_16t")) {
		throw "Bad cast exception!\n";
	}
	return DataChar16T;
};

char32_t AnyType::ToChar32_T() {
	if (type.compare("wchar_32t")) {
		throw "Bad cast exception!\n";
	}
	return DataChar32T;
};

int AnyType::ToInt() {
	if (type.compare("int")) {
		throw "Bad cast exception!\n";
	}
	return DataInt;
};

unsigned int AnyType::ToUnsignedInt() {
	if (type.compare("unsigned int")) {
		throw "Bad cast exception!\n";
	}
	return DataUnsInt;
};

short int AnyType::ToShortInt() {
	if (type.compare("short")) {
		throw "Bad cast exception!\n";
	}
	return DataShortInt;
};

unsigned short int AnyType::ToUnsignedShortInt() {
	if (type.compare("unsigned short")) {
		throw "Bad cast exception!\n";
	}
	return DataUnsShortInt;
};

long int AnyType::ToLongInt() {
	if (type.compare("long")) {
		throw "Bad cast exception!\n";
	}
	return DataLInt;
};

unsigned long int AnyType::ToUnsignedLongInt() {
	if (type.compare("unsigned long")) {
		throw "Bad cast exception!\n";
	}
	return DataUnsLInt;
};

long long int AnyType::ToLongLongInt() {
	if (type.compare("__int64")) {
		throw "Bad cast exception!\n";
	}
	return DataLLInt;
};

unsigned long long int AnyType::ToUnsignedLongLongInt() {
	if (type.compare("unsigned __int64")) {
		throw "Bad cast exception!\n";
	}
	return DataUnsLLInt;
};

float AnyType::ToFloat() {
	if (type.compare("float")) {
		throw "Bad cast exception!\n";
	}
	return DataFloat;
};

double AnyType::ToDouble() {
	if (type.compare("double")) {
		throw "Bad cast exception!\n";
	}
	return DataDouble;
};

long double AnyType::ToLongDouble() {
	if (type.compare("long double")) {
		throw "Bad cast exception!\n";
	}
	return DataLDouble;
};
