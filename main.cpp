#include "vartmpl.h"
#include <iostream>

template <typename T, T ... Is>
void print_integer_sequence(integer_sequence<T,Is...>)
{
    ((std::cout << Is << std::endl),...);
}

int main()
{
    print_integer_sequence(tail<int,1,2,3>{});
    print_integer_sequence(tail<integer_sequence<int,1,2,3>>{});
}

