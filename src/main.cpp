#include <iostream>
#include "equation.hpp"

int main(int argc, char *argv[])
{
    Equation e;
    cin>>e;
    cout<<e.expression() << " = "<<e.count();
}
