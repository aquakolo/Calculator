#include <functional>
#include <map>
#include <valarray>
#include "expression.hpp"
#include <cmath>

std::map<char, std::function<double(double, double)>> binOp = {
        {'+', [](double a, double b){return a+b;}},
        {'-', [](double a, double b){return a-b;}},
        {'*', [](double a, double b){return a*b;}},
        {'/', [](double a, double b){return a/b;}},
        {'%', [](double a, double b){return fmod(a, b);}},
        {'^', [](double a, double b){return pow(a, b);}}
};

std::string BinOp::exp() {
    return this->e1->exp() + " " + this->sign + " " + this->e2->exp();
}

double BinOp::count() {
    return binOp[this->sign](this->e1->count(), this->e2->count());
}

BinOp::BinOp(char c) {
    this->sign = c;
}

void BinOp::addExp(Expression *exp1, Expression *exp2) {
    this->e1 = std::unique_ptr<Expression>(exp1);
    this->e2 = std::unique_ptr<Expression>(exp2);
}

std::string BracketExpression::exp() {
    return "( " + this->e1->exp() + " )";
}

double BracketExpression::count() {
    return this->e1->count();
}

BracketExpression::BracketExpression(Expression *e) {
    this->e1 = std::unique_ptr<Expression>(e);
}

std::string Value::exp() {
    return std::to_string(this->value);
}

double Value::count() {
    return this->value;
}

Value::Value(double d) {
    this->value = d;
}
