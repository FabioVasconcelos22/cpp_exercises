#include <iostream>
#include <string>
#include <vector>

//#include "version.h"
//void version();

//Configuration
struct settings
{
public:
    std::string type = "";
    std::string model = "";
    std::string path = "";
    std::string country = "";
} config;

enum Error {
    InvalidOption = 0,
};

//Error Struct to handle errors
struct error_struct {
  int type;
  std::string msg;
};

class IAction {
public:
    virtual void Run () = 0;
};

class Act_BillAcceptor : public IAction {
public:
    void Run () override {
        std::cout << "BILL ACCEPTOR!" << std::endl;
        config.type = "Bill_Acceptor";
        //Preciso de tipo de aceitador, país e path
    }
};

class Act_Printer : public IAction {
public:
    void Run () override {
        std::cout << "PRINTER!" << std::endl;
        config.type = "Printer";
        //Preciso de tipo de impressora e path
    }
};

class Act_CardReader : public IAction {
public:
    void Run () override {
        std::cout << "CARD READER!" << std::endl;
        config.type = "Card_Reader";
        //Preciso de tipo de cardreader e path
    }
};

class Act_RFID : public IAction {
public:
    void Run () override {
        std::cout << "RFID!" << std::endl;
        config.type = "RFID";
        //Preciso de tipo de rfid
    }
};

class ExitAction : public IAction {
public:
    void Run () override {
        std::cout << "Bye Bye" << std::endl;
        std::exit(0);
    }
};



struct MenuItem {
public:

    std::string Text;
    IAction *   Action;

};

class MyMenu {

    private:
        std::vector <MenuItem>  _menuItems;

    public:  

        MyMenu(std::vector <MenuItem> const & menuItems) :
            _menuItems (menuItems)
        {}
        
        void printMenu() const
        {
            for(int i=0; i< _menuItems.size(); i++)
            {
                std::cout << i << " - " << _menuItems.at(i).Text << std::endl;
            }   
        }

        void runMenuItem (int input) {
            
            // Validate input
            if (input > _menuItems.size()-1) {
                throw error_struct{InvalidOption,"Try another option"};
            }

            //Run input
            _menuItems.at(input).Action->Run();
        }
};

int main(int argc, char **argv) 
{    
    int option;

    MyMenu Menu ({
        { "Bill Acceptor", new Act_BillAcceptor () },
        { "Printer", new Act_Printer () },
        { "Card Reader", new Act_CardReader () },
        { "RFID", new Act_RFID () },
        { "Exit", new ExitAction () }
    });

    for (;;) {
        Menu.printMenu();
        std::cin >> option;
        
        try {
            Menu.runMenuItem (option);
        }
        catch(error_struct e) {
            std::cerr << "\n Error type: " << e.type << ". \n"
            << "Error Message: " << e.msg << "\n" << std::endl;
        }
    }

   std::cout << "type:" << config.type << std::endl;
    
    return 0; 
}