#include <iostream>
#include <string>
#include <vector>

//#include "version.h"
//void version();


std::vector<std::string> Peripherals = {
    "Bill Acceptor",
    "Printer",
    "CardReader",
    "RFID",
};

std::vector<std::string> BillAcceptor = {
    "Enable",
    "Disable",
    "Accept",
    "Reject",
};

class MyMenu {
    
    public:  
        void printMenu(std::vector<std::string> _menu)
        {
            int _NumberOfElements = _menu.size();

            for(int i=0; i< _NumberOfElements; i++)
            {
                std::cout << i << " - " << _menu.at(i)<< std::endl;
            }   
        }
};

int main(int argc, char **argv) 
{
    //API version
    //version();

    MyMenu Menu;

    Menu.printMenu(Peripherals);
    Menu.printMenu(BillAcceptor);

    return 0;
}

/*void version()
{
  std::cout << "Welcome to verison:  "
    << SAMPLE_VERSION_MAJOR <<
    "." << SAMPLE_VERSION_MINOR <<
    "." << SAMPLE_VERSION_PATCH << std::endl;
}*/