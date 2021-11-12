#ifndef ANYTYPE_H
#define ANYTYPE_H

#include <string>

class AnyType {
  enum {        //type of variable
    boolean,

    character,
    signed_char,
    unsigned_char,
    widechar,
    char_16,
    char_32,

    integer,
    unsigned_int,
    short_int,
    unsigned_short_int,
    long_int,
    unsigned_long_int,
    long_long_int,
    unsigned_long_long_int,

    floating_point,
    floating_double,
    floating_long_double

  } vartype;  // Define one

  union {  //memory to store our variable
    bool b;

    char c;
    signed char sc;
    unsigned char usc;
    wchar_t wch;
    char16_t ch16;
    char32_t ch32;

    int i;
    unsigned int ui;
    short int si;
    unsigned short int usi;
    long int li;
    unsigned long int uli;
    long long int lli;
    unsigned long long int ulli;

    float f;
    double d;
    long double ld;
  };

  std::string vartype_str; //stores var type as a string

public:

//overloaded constructors
  AnyType(bool bb);

  AnyType(char ch);
  AnyType(signed char ch);
  AnyType(unsigned char ch);
  AnyType(wchar_t wchar);
  AnyType(char16_t ch16);
  AnyType(char32_t ch32);

  AnyType(int ii);
  AnyType(unsigned int ii);
  AnyType(short int ii);
  AnyType(unsigned short int ii);
  AnyType(long int ii);
  AnyType(unsigned long int ii);
  AnyType(long long int ii);
  AnyType(unsigned long long int ii);

  AnyType(float ff);
  AnyType(double dd);
  AnyType(long double dd);

  ~AnyType();

  //print the value
  void print() const;

  //return value
  bool ToBool() const;

  char ToChar() const;
  signed char ToSChar() const;
  unsigned char ToUChar() const;
  wchar_t ToWchar() const;
  char16_t ToChar16() const;
  char32_t ToChar32() const;

  int ToInt() const;
  unsigned int ToUInt() const;
  short int ToShortInt() const;
  unsigned short int ToUShortInt() const;
  long int ToLongInt() const;
  unsigned long int ToULongInt() const;
  long long int ToLongLongInt() const;
  unsigned long long int ToULongLongInt() const;

  float ToFloat() const;
  double ToDouble() const;
  long double ToLongDouble() const;

  //assignment overloads
  AnyType& operator=(const bool& right);

  AnyType& operator=(const char& right);
  AnyType& operator=(const signed char& right);
  AnyType& operator=(const unsigned char& right);
  AnyType& operator=(const wchar_t& right);
  AnyType& operator=(const char16_t& right);
  AnyType& operator=(const char32_t& right);

  AnyType& operator=(const int& right);
  AnyType& operator=(const unsigned int& right);
  AnyType& operator=(const short int& right);
  AnyType& operator=(const unsigned short int& right);
  AnyType& operator=(const long int& right);
  AnyType& operator=(const unsigned long int& right);
  AnyType& operator=(const long long int& right);
  AnyType& operator=(const unsigned long long int& right);

  AnyType& operator=(const float& right);
  AnyType& operator=(const double& right);
  AnyType& operator=(const long double& right);

  AnyType& operator=(const AnyType& right);

  //swap value overloads
  void swap(bool& out);

  void swap(char& out);
  void swap(signed char& out);
  void swap(unsigned char& out);
  void swap(wchar_t& out);
  void swap(char16_t& out);
  void swap(char32_t& out);

  void swap(int& out);
  void swap(unsigned int& out);
  void swap(short int& out);
  void swap(unsigned short int& out);
  void swap(long int& out);
  void swap(unsigned long int& out);
  void swap(long long int& out);
  void swap(unsigned long long int& out);

  void swap(float& out);
  void swap(double& out);
  void swap(long double& out);

  //swap with other object of this class type
  AnyType& swap(AnyType& other);

//return type of currently stored variable
 std::string getStoredType() const
 {
    return vartype_str;
 }
};

#endif // ANYTYPE_H
