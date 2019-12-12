#include <iostream>
#include <string.h>
#include <fstream>

class IOperation {
public:
    virtual float Calc (int a, int b) = 0;
};

class Sum: public IOperation{
public:
    float Calc(int a, int b) override
    {
        return a + b;
    }
};

class Subtraction: public IOperation{
public:
    float Calc(int a, int b) override
    {
        return a - b;
    }
};

class Multiplication: public IOperation{
public:
    float Calc(int a, int b) override
    {
        return a * b;
    }
};

class Division: public IOperation{
public:
    float Calc(int a, int b) override
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

class ILogger {
public:
    virtual void Log (float result) = 0;
};

class SaveFile: public ILogger{
public:
    void Log(float result) override 
    {
        //Open file
        std::ofstream ResultFile("Result.txt");
        
        //Write result
        ResultFile << result;
        
        //close file
        ResultFile.close();

        std::cout << "Saved to File" << std::endl;
    }
};

class TerminalPrint: public ILogger{
public:
    void Log(float result) override 
    {
        std::cout << "Result: " << result << std::endl;
    }
};

ILogger* getLogger(int i)
{
    if( i==0 )
    {
        return new TerminalPrint;
    }
    else if ( i==1 )
    {
        return new SaveFile;
    }
    else
    {
        std::cout << "Logger not defined" << std::endl;
    }
};


int main (int arg_c, char ** arg_v) {
    
    int file = 0;

    // parse
    int a = std::stoi(arg_v[1]);
    int b = std::stoi(arg_v[2]);
    char opId = arg_v[3][0];

    if(arg_c == 5 && strcmp(arg_v[4],"-f") == 0)
    {
        file = 1;
    }

    // get calc
    auto * op = getOperation (opId);
   
    auto * log = getLogger (file);

    log->Log(op->Calc(a,b));

    return 0;
}