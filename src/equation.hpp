#include "expression.hpp"

class Equation{

    std::shared_ptr<Expession> expression;
    static Expression * stringToExpresion(string s);

public:

    Equation() = default;
    Equation(Expression * e);
    ~Equation() = default;

    friend void operator>>(istream& s, Equation& e);

    double count();
    std::shared_ptr<const Expression> structure();
    string expression();

}