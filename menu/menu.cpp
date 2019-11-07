#include <iostream>
#include <string>
#include <vector>

//#include "version.h"
//void version();

struct settings
{
public:
    std::string type = "";
    std::string model = "";
    std::string path = "";
    std::string country = "";
} config;

class IAction {
public:
    virtual void Run () = 0;
};

class Action_A : public IAction {
public:
    void Run () override {
        std::cout << "BILL ACCEPTOR!" << std::endl;
        config.type = "Bill_Acceptor";
        //Preciso de tipo de aceitador, país e path
    }
};

class Action_B : public IAction {
public:
    void Run () override {
        std::cout << "PRINTER!" << std::endl;
        config.type = "Printer";
        //Preciso de tipo de impressora e path
    }
};

class Action_C : public IAction {
public:
    void Run () override {
        std::cout << "CARD READER!" << std::endl;
        config.type = "Card_Reader";
        //Preciso de tipo de cardreader e path
    }
};

class Action_D : public IAction {
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
        uint64_t                _timestamp;

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
            // validar input

            // throw

            // -> run()

        }
};

int main(int argc, char **argv) 
{
    //API version
    //version();
    
    int option;

    MyMenu Menu ({
        { "Bill Acceptor", new Action_A () },
        { "Printer", new Action_B () },
        { "Card Reader", new Action_C () },
        { "RFID", new Action_D () },
        { "Exit", new ExitAction () }
    });

    for (;;) {
        Menu.printMenu();
        std::cin >> option;
        Menu.runMenuItem (option);
    }

    std::cout << "type:" << config.type << std::endl;
    return 0;
}

/*void version()
{
  std::cout << "Welcome to verison:  "
    << SAMPLE_VERSION_MAJOR <<
    "." << SAMPLE_VERSION_MINOR <<
    "." << SAMPLE_VERSION_PATCH << std::endl;
}*/