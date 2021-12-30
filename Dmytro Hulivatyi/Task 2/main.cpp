#include <iostream>
#include <stdexcept>
#include "AnyType.h"

int main()
{
    using namespace std;

    AnyType val1(1), val2(2), val3(3);
    float test1{4.0f};
    double test2{5.0d};
    char test3{'a'};
    wchar_t wch = L'b';

    val1 = val2 = val3;
    val1.print(); val2.print(); val3.print();

    val1 = test1;
    val1.print();
    val1 = test2;
    val1.print();

    val1 = 'f';
    val1=false;

    float outside = 0.0f;
    try
    {
        outside = val1.ToFloat();
    }
    catch(const runtime_error& err)
      {
        cout << err.what() << endl;
      }

    val2 = 5;
    int outside1 = 6;
    val2.swap(outside1);
    val2.print();
    cout << "\n " << outside1 << endl;

    val3=9;
    val2.swap(val3);
    val2.print(); cout << endl;
    val3.print(); cout << endl;

    cout << val3.getStoredType() << endl;
    return 0;
}
