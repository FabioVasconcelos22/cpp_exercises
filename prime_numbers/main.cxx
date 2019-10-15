#include <iostream>

bool isPrime(int number)
{
  if (number <= 0)
  {
    throw -1;
  }

  if (number == 1)
  {
    throw 1;
  }
  
  for(int i=2; i<number; i++)
  {
    if(number%i == 0)
    {
      return false;
    }
  }
  return true;
}

int main (int argc, char *argv[])
{
  int Min_number = 0;
  int Max_number = 0;

  switch(argc)
  {    
    case 2:
      Min_number = atoi(argv[1]);

      try
      {
        if(isPrime(Min_number))
        {
          std::cout << "The number " << Min_number << " is prime." << std::endl;
        }
        else
        {
          std::cout << "The number " << Min_number << " is not prime." << std::endl;
        }
      } catch(int e)
      {
          std::cout << "Exception: " << e << std::endl;
      }
      break;

    case 3:
      Min_number = atoi(argv[1]);
      Max_number = atoi(argv[2]);

      if (Max_number <= Min_number)
      {
        std::cout << "Your Min_number is bigger than Max_numbers. Maybe you switched the arguments" << std::endl;
        return 0;
      }

      try
      {
        isPrime(Min_number);
        isPrime(Max_number);
      } catch(int e)
      {
          std::cout << "Exception: " << e << std::endl;
      }

      std::cout << "The prime numbers between this limits are:"<< std::endl;

      for(int i = Min_number; i<= Max_number; i++)
      {
        if(isPrime(i))
        {
          std::cout << i << std::endl;
        }
      }
      break;
    
    default:
      std::cout << "You should pass some arguments to our app. E.g:" << std::endl;
      std::cout << "./Primers X -> if you want to know if number X is primer" << std::endl;
      std::cout << "./Primers X Y -> if you want to know the prime numbers between [ X,Y ]" << std::endl;
      break;
  }
  return 0;
}