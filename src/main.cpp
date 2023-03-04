#include <iostream>
#include "equation.hpp"

int main()
{
    Equation e;
    std::cin>>e;
    std::cout<<e.toString() << " = "<<e.count();
}
