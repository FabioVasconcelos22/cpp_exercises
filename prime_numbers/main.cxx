#include <iostream>

bool isPrime(int number)
{
  if (number <= 0)
  {
    std::cout << "The number " << number << " is not a natural number" << std::endl;
    return false;
  }
  else if (number == 1)
  {
    std::cout << "By definition, number 1 is an exception." << std::endl;
    return false;
  }
  else
  {
    for(int i=2; i<number; i++)
    {
      if(number%i == 0)
      {
        return false;
      }
    }
  }
}

int main (int argc, char *argv[])
{
  int Min_number = 0;
  int Max_number = 0;

  switch(argc)
  {    
    case 2:
      Min_number = atoi(argv[1]);

      if(isPrime(Min_number))
      {
        std::cout << "The number " << Min_number << " is prime." << std::endl;
      }
      else
      {
        std::cout << "The number " << Min_number << " is not prime." << std::endl;
      }
      break;

    case 3:
      Min_number = atoi(argv[1]);
      Max_number = atoi(argv[2]);

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