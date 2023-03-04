#include <memory>
#include "expression.hpp"

class Equation{

    std::shared_ptr<Expression> expression;

public:

    static Expression * stringToExpression(const std::string& s);

    Equation() = default;

    explicit Equation(const std::shared_ptr<Expression> &expression);

    ~Equation() = default;

    friend void operator>>(std::istream& s, Equation& e);

    double count();
    std::shared_ptr<Expression> structure() {
        return expression;
    }

    std::string toString();

};