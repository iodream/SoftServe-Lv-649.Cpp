#ifndef MYCLASS_HPP_SENTRY
#define MYCLASS_HPP_SENTRY

class MyClass {
    /* two integer members
       default initialized
    */
    int x{};
    int y{};
public:
    // Default constructor
    MyClass() {}
    // Some function \
       and bad multiline comment
    Foo() {}

    // Destructor for some reason preceded by blank line
    ~MyClass() {}
};

#endif
