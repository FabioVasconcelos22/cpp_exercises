#include <iostream>

//Error Struct to handle errors
struct error_struct {
  int type;
  std::string msg;
};

//Algorithm to check if number is prime or not
bool CheckPrime(int number)
{  
  for(int i=2; i<number/2+1; i++)
  {
    if(number%i == 0)
      return false;
  }
  return true;
}

//Print to the console is number is prime or not
void isPrime(int number)
{
  if (CheckPrime(number))
    std::cout << "The number " << number << " is prime." << std::endl;
  else
    std::cout << "The number " << number << " is not prime." << std::endl;
}

//Validate if introduced number is valid
bool Validate_number(int number)
{
  if (number <= 0)
  {
    throw error_struct{0,"Please insert a natural number. (N>0)"};
    return false;
  }

  if (number == 1)
  {
    throw error_struct{1,"Number 1 is an exception."};
    return false;
  }
  return true;
}

//Validate if introduced numbers are valid
bool Validate_number(int number1, int number2)
{
  if (number1 <= 0 || number2 <= 0)
  {
    throw error_struct{0,"Please insert natural numbers. (N>0)"};
    return false;
  }

  if (number1 == 1 || number2 == 1)
  {
    throw error_struct{1,"Number 1 is an exception."};
    return false;
  }

  if (number1 >= number2)
  {
    throw error_struct{2,"Your min_limit is higher than max_limit."};
    return false;
  }
  return true;
}

void GameRules()
{
  std::cout << "You should pass some arguments to our app. E.g:" << std::endl;
  std::cout << "./Primers X -> if you want to know if number X is primer" << std::endl;
  std::cout << "./Primers X Y -> if you want to know the prime numbers between [ X,Y ]" << std::endl;
}


int main (int argc, char *argv[])
{
  int Min_number = 0;
  int Max_number = 0;

  try
  {
    switch(argc)
    {    
      case 2: //Check just a number
        Min_number = atoi(argv[1]);
        Validate_number(Min_number);
        isPrime(Min_number);
        break;

      case 3: //Check interval
        Min_number = atoi(argv[1]);
        Max_number = atoi(argv[2]);
        Validate_number(Min_number, Max_number);
        
        for(int i = Min_number; i<= Max_number; i++)
        {
          isPrime(i);
        }
        break;
      
      default:
        GameRules();
        break;
    }
  } catch(error_struct e)
  {
    std::cout << "Error Code: " << e.type << " -> " << e.msg << std::endl;
  }
  return 0;
}