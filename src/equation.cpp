#include "equation.hpp"
#include "expression.hpp"
#include <list>

class Equation{

    public:

    Equation(Expression * e){
        expression = std::make_shared<Expression>(e);
    }

    friend void operator>>(Equation& e, istream% s){
        string exp;
        std::getline(std::cin, exp, '=');
        expression = std::make_shared<Expression>(stringToExpresion(exp));
    }

    double count(){
        return expression.count();
    }
    std::shared_ptr<const Expression> structure(){
        return expression;
    }
    string expression(){
        return expression.exp();
    }

    private:
    
    static Expression * stringToExpresion(string s){
        std::list<std::string>
        string value;
        for(char c : s){

        }
    }
}