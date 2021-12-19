#include <string>
#include <typeinfo>

class AnyType {
private:
	std::string type;
	union {
		bool DataBool;
		char DataChar;
		signed char DataSChar;
		unsigned char DataUnsChar;
		wchar_t DataWCharT;
		char16_t DataChar16T;
		char32_t DataChar32T;
		int DataInt;
		unsigned int DataUnsInt;
		short int DataShortInt;
		unsigned short int DataUnsShortInt;
		long int DataLInt;
		unsigned long int DataUnsLInt;
		long long int DataLLInt;
		unsigned long long int DataUnsLLInt;
		float DataFloat;
		double DataDouble;
		long double DataLDouble;
	};
public:
	AnyType();
	void Swap(AnyType&);
	std::string GetType();
	
	template <typename T>
	AnyType(T data) {
		type = typeid(data).name();
		if (!type.compare("bool")) {
			DataBool = data;
		}
		else if (!type.compare("char")) {
			DataChar = data;
		}
		else if (!type.compare("signed char")) {
			DataSChar = data;
		}
		else if (!type.compare("unsigned char")) {
			DataUnsChar = data;
		}
		else if (!type.compare("wchar_t")) {
			DataWCharT = data;
		}
		else if (!type.compare("char16_t")) {
			DataChar16T = data;
		}
		else if (!type.compare("char32_t")) {
			DataChar32T = data;
		}
		else if (!type.compare("int")) {
			DataInt = data;
		}
		else if (!type.compare("unsigned int")) {
			DataUnsInt = data;
		}
		else if (!type.compare("short")) {
			DataShortInt = data;
		}
		else if (!type.compare("unsigned short")) {
			DataUnsShortInt = data;
		}
		else if (!type.compare("long")) {
			DataLInt = data;
		}
		else if (!type.compare("unsigned long")) {
			DataUnsLInt = data;
		}
		else if (!type.compare("__int64")) {
			DataLLInt = data;
		}
		else if (!type.compare("unsigned __int64")) {
			DataUnsLLInt = data;
		}
		else if (!type.compare("float")) {
			DataFloat = data;
		}
		else if (!type.compare("double")) {
			DataDouble = data;
		}
		else if (!type.compare("long double")) {
			DataLDouble = data;
		}
		else {
			type = "None";
		}
	}

	template<typename T>
	AnyType& operator=(T data) {
		std::string tempType = typeid(data).name();
		if (type == tempType) {
			return *this;
		}
		if (!tempType.compare("bool")) {
			DataBool = data;
			type = tempType;
		}
		else if (!tempType.compare("char")) {
			DataChar = data;
			type = tempType;
		}
		else if (!tempType.compare("signed char")) {
			DataSChar = data;
			type = tempType;
		}
		else if (!tempType.compare("unsigned char")) {
			DataUnsChar = data;
			type = tempType;
		}
		else if (!tempType.compare("wchar_t")) {
			DataWCharT = data;
			type = tempType;
		}
		else if (!tempType.compare("char16_t")) {
			DataChar16T = data;
			type = tempType;
		}
		else if (!tempType.compare("char32_t")) {
			DataChar32T = data;
			type = tempType;
		}
		else if (!tempType.compare("int")) {
			DataInt = data;
			type = tempType;
		}
		else if (!tempType.compare("unsigned int")) {
			DataUnsInt = data;
			type = tempType;
		}
		else if (!tempType.compare("short")) {
			DataShortInt = data;
			type = tempType;
		}
		else if (!tempType.compare("unsigned short")) {
			DataUnsShortInt = data;
			type = tempType;
		}
		else if (!tempType.compare("long")) {
			DataLInt = data;
			type = tempType;
		}
		else if (!tempType.compare("unsigned long")) {
			DataUnsLInt = data;
			type = tempType;
		}
		else if (!tempType.compare("__int64")) {
			DataLLInt = data;
			type = tempType;
		}
		else if (!tempType.compare("unsigned __int64")) {
			DataUnsLLInt = data;
			type = tempType;
		}
		else if (!tempType.compare("float")) {
			DataFloat = data;
			type = tempType;
		}
		else if (!tempType.compare("double")) {
			DataDouble = data;
			type = tempType;
		}
		else if (!tempType.compare("long double")) {
			DataLDouble = data;
			type = tempType;
		}
		return *this;
	}

	bool ToBool();
	char ToChar();
	signed ToSignedChar();
	unsigned char ToUnsignedChar();
	wchar_t ToWChar_T();
	char16_t ToChar16_T();
	char32_t ToChar32_T();
	int ToInt();
	unsigned int ToUnsignedInt();
	short int ToShortInt();
	unsigned short int ToUnsignedShortInt();
	long int ToLongInt();
	unsigned long int ToUnsignedLongInt();
	long long int ToLongLongInt();
	unsigned long long int ToUnsignedLongLongInt();
	float ToFloat();
	double ToDouble();
	long double ToLongDouble();
};
