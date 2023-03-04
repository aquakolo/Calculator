#include <string>
#include <memory>

class Expression{
public:
    virtual std::string exp() = 0;
    virtual double count() = 0;
};

class BinOp : public Expression {
    std::unique_ptr<Expression> e1, e2;
    char sign;
public:
    void addExp(std::unique_ptr<Expression> &exp1, std::unique_ptr<Expression> &exp2);
    std::string exp() override;
    double count() override;

    explicit BinOp(char c);
};

class BracketExpression : public Expression{
    std::unique_ptr<Expression> e1;
public:
    BracketExpression() = default;
    void addExp(std::unique_ptr<Expression> &exp);
    std::string exp() override;
    double count() override;
};

class Value : public Expression {
    double value;
public:
    explicit Value(double d);
    std::string exp() override;
    double count() override;
};
