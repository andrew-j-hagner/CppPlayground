#include <iostream>
#include <stdbool.h>

int forwardDeclaredFunction(int x); // Forward declaration

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << forwardDeclaredFunction(2) << std::endl;
    // std::cout << is_odd_AltA(2) << std::endl;
    return 0;
}

int forwardDeclaredFunction(int x) // Definition of the forward-declared function
{
    return x & 1; // what an odd function!
}

// Not forward-declared functions
bool is_odd_AltA(int x) { return x % 2; }
int is_odd_AltB(int x) { return x % 2 != 0; }
int is_odd_AltC(unsigned int x) { return x % 2 != 0; }
bool is_odd_AltD(unsigned int x) { return x & 1; }

bool is_odd_LinkerError(unsigned int x); // Never defined, will cause linker error

int circularFunctionY(int x);
int circularFunctionX(int x)
{
    circularFunctionY(1);
    return x;
}

int circularFunctionY(int x)
{
    circularFunctionX(1);
    return x;
}
