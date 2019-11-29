#include <iostream>

class IOperation {
public:
    virtual int Calc (int a, int b) = 0;
};

class Sum: public IOperation{
public:
    int Calc(int a, int b) override
    {
        return a + b;
    }
};

class Subtraction: public IOperation{
public:
    int Calc(int a, int b) override
    {
        return a - b;
    }
};

class Multiplication: public IOperation{
public:
    int Calc(int a, int b) override
    {
        return a * b;
    }
};

class Division: public IOperation{
public:
    int Calc(int a, int b) override
    {
        return a / b;
    }
};

IOperation* getOperation(char op)
{
    if (op == '+'){
        return new Sum;
    }
    else if (op == '-') {
        return new Subtraction;
    }
    else if (op == '*') {
        return new Multiplication;
    }
    else if (op == '/') {
        return new Division;
    }
    else
    {
        std::cout << "Not defined" << std::endl;
    }
    
}


int main (int arg_c, char ** arg_v) {
    
    // parse
    int a = std::stoi(arg_v[1]);
    int b = std::stoi(arg_v[2]);
    char opId = arg_v[3][0];

    // get calc
    auto * op = getOperation (opId);

    std::cout << "Result: " << op->Calc (a, b) << std::endl;


    return 0;
}