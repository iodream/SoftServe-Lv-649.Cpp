#include "AnyType.h"
#include <iostream>
#include <stdexcept>
#include <locale>    //for wstring conversion
#include <codecvt>
#include <algorithm> //for std::swap


//required for char16 and char32 printing
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;

AnyType::AnyType(bool bb)
{
  vartype = boolean;
  vartype_str="bool";
  b = bb;
}

AnyType::AnyType(char ch)
{
  vartype = character;
  vartype_str="char";
  c = ch;
}

AnyType::AnyType(signed char ch)
{
  vartype = signed_char;
  vartype_str="signed char";
  sc = ch;
}

AnyType::AnyType(unsigned char ch)
{
  vartype = unsigned_char;
  vartype_str="unsigned char";
  usc = ch;
}

AnyType::AnyType(wchar_t wchar)
{
  vartype = widechar;
  vartype_str="wchar_t";
  wch = wchar;
}

AnyType::AnyType(char16_t ch16)
{
  vartype = char_16;
  vartype_str="char16_t";
  this->ch16 = ch16;
}

AnyType::AnyType(char32_t ch32)
{
  vartype = char_32;
  vartype_str="char32_t";
  this->ch32 = ch32;
}

AnyType::AnyType(int ii)
{
  vartype = integer;
  vartype_str="int";
  i = ii;
}

AnyType::AnyType(unsigned int ii)
{
  vartype = unsigned_int;
  vartype_str="unsigned int";
  ui = ii;
}

AnyType::AnyType(short int ii)
{
  vartype = short_int;
  vartype_str="short int";
  si = ii;
}

AnyType::AnyType(unsigned short int ii)
{
  vartype = unsigned_short_int;
  vartype_str="unsigned short int";
  usi = ii;
}

AnyType::AnyType(long int ii)
{
  vartype = long_int;
  vartype_str="long int";
  li = ii;
}

AnyType::AnyType(unsigned long int ii)
{
  vartype = unsigned_long_int;
  vartype_str="unsigned long int";
  uli = ii;
}

AnyType::AnyType(long long int ii)
{
  vartype = long_long_int;
  vartype_str="long long int";
  lli = ii;
}

AnyType::AnyType(unsigned long long int ii)
{
  vartype = unsigned_long_long_int;
  vartype_str="unsigned long long int";
  ulli = ii;
}

AnyType::AnyType(float ff)
{
  vartype = floating_point;
  vartype_str="float";
  f = ff;
}

AnyType::AnyType(double dd)
{
  vartype = floating_double;
  vartype_str="double";
  d = dd;
}

AnyType::AnyType(long double dd)
{
  vartype = floating_long_double;
  vartype_str="long double";
  ld = dd;
}

//destructor
AnyType::~AnyType()
{

}

void AnyType::print() const
{
 using namespace std;
 switch (vartype) {
    case boolean:
       cout << vartype_str << " " << b << endl;
       break;
    case character:
       cout << vartype_str << " " << c << endl;
       break;
    case signed_char:
       cout << vartype_str << " " << sc << endl;
       break;
    case unsigned_char:
       cout << vartype_str << " " << usc << endl;
       break;
     case widechar:
       cout << vartype_str << " "; wcout<< wch << endl;
       break;
     case char_16:
       cout << vartype_str << " " << myconv.to_bytes(ch16) << endl;
       break;
     case char_32:
       cout << "char32_t: " << myconv.to_bytes(ch32) << endl;
       break;

    case integer:
       cout << vartype_str << " " << i << endl;
       break;
    case unsigned_int:
       cout << vartype_str << " " << ui << endl;
       break;
    case short_int:
       cout << vartype_str << " " << si << endl;
       break;
    case long_int:
       cout << vartype_str << " " << li << endl;
       break;
    case unsigned_long_int:
       cout << vartype_str << " " << uli << endl;
       break;
    case unsigned_short_int:
       cout << vartype_str << " " << usi << endl;
       break;
    case long_long_int:
       cout << vartype_str << " " << lli << endl;
       break;
    case unsigned_long_long_int:
       cout << vartype_str << " " << ulli << endl;
       break;

    case floating_point:
       cout << vartype_str << " " << f << endl;
       break;
    case floating_double:
       cout << vartype_str << " " << d << endl;
       break;
    case floating_long_double:
       cout << vartype_str << " " << ld << endl;
       break;
    default:
       cout << "unknown vartype!" << endl;
       break;
  }
}


bool AnyType::ToBool() const
{
    if(vartype!=boolean)
        throw std::runtime_error("bad cast");
    return b;
}

char AnyType::ToChar() const
{
    if(vartype!=character)
        throw std::runtime_error("bad cast");
    return c;
}

signed char AnyType::ToSChar() const
{
    if(vartype!=signed_char)
        throw std::runtime_error("bad cast");
    return sc;
}

unsigned char AnyType::ToUChar() const
{
    if(vartype!=unsigned_char)
        throw std::runtime_error("bad cast");
    return usc;
}

wchar_t AnyType::ToWchar() const
{
    if(vartype!=widechar)
        throw std::runtime_error("bad cast");
    return wch;
}

char16_t AnyType::ToChar16() const
{
    if(vartype!=char_16)
        throw std::runtime_error("bad cast");
    return ch16;
}

char32_t AnyType::ToChar32() const
{
    if(vartype!=char_32)
        throw std::runtime_error("bad cast");
    return ch32;
}

int AnyType::ToInt() const
{
    if(vartype!=integer)
        throw std::runtime_error("bad cast");
    return i;
}

unsigned int AnyType::ToUInt() const
{
    if(vartype!=unsigned_int)
        throw std::runtime_error("bad cast");
    return ui;
}

short int AnyType::ToShortInt() const
{
    if(vartype!=short_int)
        throw std::runtime_error("bad cast");
    return si;
}

unsigned short int AnyType::ToUShortInt() const
{
    if(vartype!=unsigned_short_int)
        throw std::runtime_error("bad cast");
    return usi;
}

long int AnyType::ToLongInt() const
{
    if(vartype!=long_int)
        throw std::runtime_error("bad cast");
    return li;
}

unsigned long int AnyType::ToULongInt() const
{
    if(vartype!=unsigned_long_int)
        throw std::runtime_error("bad cast");
    return uli;
}

long long int AnyType::ToLongLongInt() const
{
    if(vartype!=long_long_int)
        throw std::runtime_error("bad cast");
    return lli;
}

unsigned long long int AnyType::ToULongLongInt() const
{
    if(vartype!=unsigned_long_long_int)
        throw std::runtime_error("bad cast");
    return ulli;
}



float AnyType::ToFloat() const
{
    if(vartype!=floating_point)
        throw std::runtime_error("bad cast");
    return f;
}


double AnyType::ToDouble() const
{
    if(vartype!=floating_double)
        throw std::runtime_error("bad cast");
    return d;
}

long double AnyType::ToLongDouble() const
{
    if(vartype!=floating_long_double)
        throw std::runtime_error("bad cast");
    return ld;
}


AnyType& AnyType::operator=(const bool& right)
{
    vartype=boolean;
    vartype_str="bool";
    b=right;
    return *this;
}



AnyType& AnyType::operator=(const char& right)
{
    vartype=character;
    vartype_str="char";
    c=right;
    return *this;
}

AnyType& AnyType::operator=(const signed char& right)
{
    vartype=signed_char;
    vartype_str="signed char";
    sc=right;
    return *this;
}

AnyType& AnyType::operator=(const unsigned char& right)
{
    vartype=unsigned_char;
    vartype_str="unsigned char";
    usc=right;
    return *this;
}

AnyType& AnyType::operator=(const wchar_t& right)
{
    vartype=widechar;
    vartype_str="wchar_t";
    wch=right;
    return *this;
}

AnyType& AnyType::operator=(const char16_t& right)
{
    vartype=char_16;
    vartype_str="char16_t";
    ch16=right;
    return *this;
}


AnyType& AnyType::operator=(const char32_t& right)
{
    vartype=char_32;
    vartype_str="char32_t";
    ch32=right;
    return *this;
}



AnyType& AnyType::operator=(const int& right)
{
    vartype=integer;
    vartype_str="int";
    i=right;
    return *this;
}

AnyType& AnyType::operator=(const unsigned int& right)
{
    vartype=unsigned_int;
    vartype_str="unsigned int";
    ui=right;
    return *this;
}

AnyType& AnyType::operator=(const short int& right)
{
    vartype=short_int;
    vartype_str="short int";
    si=right;
    return *this;
}

AnyType& AnyType::operator=(const unsigned short int& right)
{
    vartype=unsigned_short_int;
    vartype_str="unsigned short int";
    usi=right;
    return *this;
}

AnyType& AnyType::operator=(const long int& right)
{
    vartype=long_int;
    vartype_str="long int";
    li=right;
    return *this;
}

AnyType& AnyType::operator=(const long long int& right)
{
    vartype=long_long_int;
    vartype_str="long long int";
    lli=right;
    return *this;
}

AnyType& AnyType::operator=(const unsigned long long int& right)
{
    vartype=unsigned_long_long_int;
    vartype_str="unsigned long long int";
    ulli=right;
    return *this;
}



AnyType& AnyType::operator=(const float& right)
{
    vartype=floating_point;
    vartype_str="float";
    f=right;
    return *this;
}

AnyType& AnyType::operator=(const double& right)
{
    vartype=floating_double;
    vartype_str="double";
    d=right;
    return *this;
}

AnyType& AnyType::operator=(const long double& right)
{
    vartype=floating_long_double;
    vartype_str="long double";
    ld=right;
    return *this;
}


AnyType& AnyType::operator=(const AnyType& right)
{
    if(this == &right) //self-assignment
        return *this;

    vartype=right.vartype;
    vartype_str=right.vartype_str;
    switch(right.vartype)
    {
        case boolean:
          b=right.b;
          break;
        case character:
          c=right.c;
          break;
        case signed_char:
          sc=right.sc;
          break;
        case unsigned_char:
          usc=right.usc;
          break;
        case widechar:
          wch=right.wch;
          break;
        case char_16:
          ch16=right.ch16;
          break;
        case char_32:
          ch32=right.ch32;
          break;

        case integer:
          i=right.i;
          break;
        case unsigned_int:
          ui=right.ui;
          break;
        case short_int:
          si=right.si;
          break;
        case long_int:
          li=right.li;
          break;
        case unsigned_long_int:
          uli=right.uli;
          break;
        case unsigned_short_int:
          usi=right.usi;
          break;
        case long_long_int:
          lli=right.lli;
          break;
        case unsigned_long_long_int:
          ulli=right.ulli;
          break;

        case floating_point:
          f=right.f;
          break;
        case floating_double:
          d=right.d;
          break;
         case floating_long_double:
          ld=right.ld;
          break;
    }
    return *this;
}


void AnyType::swap(bool& out)
{
    std::swap(b,out);
}



void AnyType::swap(char& out)
{
    std::swap(c,out);
}

void AnyType::swap(signed char& out)
{
    std::swap(sc,out);
}

void AnyType::swap(unsigned char& out)
{
    std::swap(usc,out);
}

void AnyType::swap(wchar_t& out)
{
    std::swap(wch,out);
}

void AnyType::swap(char16_t& out)
{
    std::swap(ch16,out);
}

void AnyType::swap(char32_t& out)
{
    std::swap(ch32,out);
}


void AnyType::swap(int& out)
{

    std::swap(i,out);
}

void AnyType::swap(unsigned int& out)
{

    std::swap(ui,out);
}

void AnyType::swap(short int& out)
{

    std::swap(si,out);
}

void AnyType::swap(unsigned short int& out)
{
    std::swap(usi,out);
}

void AnyType::swap(long int& out)
{
    std::swap(li,out);
}

void AnyType::swap(unsigned long int& out)
{
    std::swap(uli,out);
}

void AnyType::swap(long long int& out)
{
    std::swap(lli,out);
}

void AnyType::swap(unsigned long long int& out)
{
    std::swap(ulli,out);
}

void AnyType::swap(float& out)
{
    std::swap(f,out);
}

void AnyType::swap(double& out)
{
    std::swap(d,out);
}

void AnyType::swap(long double& out)
{
    std::swap(ld,out);
}


//for swap between two objects
AnyType& AnyType::swap(AnyType& other)
{
    switch(other.vartype)
    {
        case boolean:
          std::swap(b,other.b);
          break;

        case character:
          std::swap(c,other.c);
          break;
        case signed_char:
          std::swap(sc,other.sc);
          break;
        case unsigned_char:
          std::swap(usc,other.usc);
          break;
        case widechar:
          std::swap(wch,other.wch);
          break;
        case char_16:
          std::swap(ch16,other.ch16);
          break;
        case char_32:
          std::swap(ch32,other.ch32);
          break;

        case integer:
          std::swap(i,other.i);
          break;
        case unsigned_int:
          std::swap(ui,other.ui);
          break;
        case short_int:
          std::swap(si,other.si);
          break;
        case long_int:
          std::swap(li,other.li);
          break;
        case unsigned_long_int:
          std::swap(uli,other.uli);
          break;
        case unsigned_short_int:
          std::swap(usi,other.usi);
          break;
        case long_long_int:
          std::swap(lli,other.lli);
          break;
        case unsigned_long_long_int:
          std::swap(ulli,other.ulli);
          break;

        case floating_point:
          std::swap(f,other.f);
          break;
        case floating_double:
          std::swap(d,other.d);
          break;
        case floating_long_double:
          std::swap(ld,other.ld);
          break;
    }
   return *this;
}
