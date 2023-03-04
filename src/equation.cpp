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
    std::list<std::unique_ptr<Expression>>::iterator iterator;
    int pos;
    Iter(int p, std::_List_iterator<std::unique_ptr<Expression>> i, int po){
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

std::unique_ptr<Expression> Equation::stringToExpression(const std::string& s){
    std::priority_queue<Iter , std::vector<Iter>, compare >pqueue;
    std::list<std::unique_ptr<Expression>> listOfElements;
    std::map<char, int> charToPriority = {
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2},
            {'%', 2},
            {'^', 3},
            };
    std::string value;
    int priority=0;
    std::_List_iterator<std::unique_ptr<Expression>> li;

    for(char c : s){

        if(c!='.' && (c<'0' || c>'9') && !value.empty()){
            listOfElements.emplace_back(std::make_unique<Value>(std::stod(value)));
            value = "";
        }

        switch(c){
            case '(':
                priority+=10;
                listOfElements.push_back(std::make_unique<BracketExpression>());
                li = std::prev(listOfElements.end());
                pqueue.emplace(priority, li, pqueue.size());
                break;
            case ')':
                priority-=10;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                listOfElements.push_back(std::make_unique<BinOp>(c));
                li = std::prev(listOfElements.end());
                pqueue.emplace(priority+charToPriority[c], li, pqueue.size());
                break;
            case '.':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                value += c;
                break;
            default:
                break;
        };
    }
    if(!value.empty()){
        listOfElements.emplace_back(std::make_unique<Value>(std::stod(value)));
        value = "";
    }
    while(!pqueue.empty()){
        auto top = pqueue.top();
        pqueue.pop();
        if(top.priority%10!=0) {
            reinterpret_cast<std::unique_ptr <BinOp> &&>(*top.iterator)->addExp(
                    *prev(top.iterator),
                    *next(top.iterator)
                    );
            listOfElements.erase(prev(top.iterator));
            listOfElements.erase(next(top.iterator));
        }
        else{
            reinterpret_cast<std::unique_ptr <BracketExpression> &&>(*top.iterator)->addExp(
                    *next(top.iterator)
            );
            listOfElements.erase(next(top.iterator));
        }
    }

    return std::move(listOfElements.front());
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

