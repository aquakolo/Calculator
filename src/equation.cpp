#include "equation.hpp"
#include <list>
#include <string>
#include <map>
#include <queue>


double Equation:: count(){
    return this->expression->count();
}



class Iter{
public:
    int priority;
    std::list<Expression *>::iterator iterator;
    int pos;
    Iter(int p, std::list<Expression *>::iterator i, int po){
        priority = p;
        iterator = i;
        pos=po;
    }
};

class compare{
public:
    bool operator()(Iter a, Iter b){
        if(a.priority!=b.priority)
            return a.priority > b.priority;
        return a.pos <  b.pos;
    }
};

Expression * Equation::stringToExpression(const std::string& s){
    std::priority_queue<Iter , std::vector<Iter>, compare >pqueue;
    std::list<Expression *> listOfElements;
    std::map<char, int> priority = {
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2},
            {'%', 2},
            {'^', 3},
            };
    std::string value;
    for(size_t c=0; c<s.size();c++){
        if(s[c] == '('){
            size_t fin = s.find_first_of(s[c], c);
            listOfElements.emplace_back(new BracketExpression(stringToExpression(s.substr(c+1, fin-c-1))));
            c=fin;
        }
        else if(priority.find(s[c]) != priority.end()){
            if(!value.empty()){
                listOfElements.emplace_back(new Value(std::stod(value)));
                value = "";
            }
            listOfElements.emplace_back(new BinOp(s[c]));
            auto li = std::prev(listOfElements.end());
            pqueue.emplace(priority[s[c]], li, c);
        }
        else if((s[c] >= '0' && s[c]<= '9') || s[c]=='.') {
            value += s[c];
        }
    }
    if(!value.empty()){
        listOfElements.emplace_back(new Value(std::stod(value)));
        value = "";
    }
    Expression * expression = listOfElements.front();
    while(!pqueue.empty()){
        auto top = pqueue.top();
        pqueue.pop();
        expression = *top.iterator;
        auto e = dynamic_cast<BinOp *>(expression);
        auto p = *prev(top.iterator);
        auto n = *next(top.iterator);
        e->addExp(p, n);
    }

    return expression;
}

void operator>>(std::istream &s, Equation &e) {
    std::string exp;
    std::getline(s, exp, '=');
    e.expression = std::shared_ptr<Expression>(Equation::stringToExpression(exp));

}

std::string Equation::toString() {
    return this->expression->exp();
}

Equation::Equation(const std::shared_ptr<Expression> &expression) : expression(expression) {}

