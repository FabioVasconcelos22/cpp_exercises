// A simple program that computes the square root of a number
#include <iostream>

bool isPrime(int number)
{
  for(int i=1; i<number; i++)
  {
    if(number%i == 0)
    {
      return false;
    }
  }
  return false;
}



int main (int argc, char *argv[])
{
  int number = atoi(argv[1]);

  if(isPrime(number))
  {
    std::cout << "The number" << number << "is prime" << std::endl;
  }
  else
  {
    std::cout << "The number" << number << "is not a prime. \n LOSER!!!!" << std::endl;
  }
  return 0;
}