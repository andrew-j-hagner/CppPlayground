#include <iostream>

int variables()
{
    std::cout << "Hello, World!" << std::endl;

    // VARIABLE INITIALIZATION EXAMPLES

    int a; // default-initialization (no initializer)

    // Traditional initialization forms:
    int b = 5; // copy-initialization (initial value after equals sign)
    int c(6);  // direct-initialization (initial value in parenthesis)

    // Modern initialization forms (preferred):
    int d{7}; // direct-list-initialization (initial value in braces)
    int e{};  // value-initialization (empty braces)

    // Example of narrowing conversion:
    int w1{4.5};  // compile error: list-init does not allow narrowing conversion
    int w2 = 4.5; // compiles: w2 copy-initialized to value 4
    int w3(4.5);  // compiles: w3 direct-initialized to value 4
    w1 = 4.5;     // okay: copy-assignment allows narrowing conversion of 4.5 to 4

    // Example of multiple initializations:
    int a, b = 5;     // wrong: a is not initialized to 5!
    int a = 5, b = 5; // correct: a and b are initialized to 5

    // Example of when to use [[maybe_unused]]:
    [[maybe_unused]] double pi{3.14159};  // Don't complain if pi is unused
    [[maybe_unused]] double gravity{9.8}; // Don't complain if gravity is unused
    [[maybe_unused]] double phi{1.61803}; // Don't complain if phi is unused

    return 0;
}
