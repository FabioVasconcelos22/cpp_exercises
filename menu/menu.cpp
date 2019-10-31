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
};

class IAction {
public:
    virtual void Run () = 0;
};

class Action_A : public IAction {
public:
    settings config;
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
        //Preciso de tipo de impressora e path
    }
};

class Action_C : public IAction {
public:
    void Run () override {
        std::cout << "CARD READER!" << std::endl;
        //Preciso de tipo de cardreader e path
    }
};

class Action_D : public IAction {
public:
    void Run () override {
        std::cout << "RFID!" << std::endl;
        //Preciso de tipo de rfid
    }
};

struct MenuItem {
public:

    std::string Text;
    IAction *   Action;

};

class MyMenu {

    private:
        std::vector <MenuItem> _menuItems;

    public:  
        MyMenu(std::vector <MenuItem> const & menuItems)
        {
            _menuItems = menuItems;        
        }
        
        void printMenu() const
        {
            for(int i=0; i< _menuItems.size(); i++)
            {
                std::cout << i << " - " << _menuItems.at(i).Text << std::endl;
            }   
        }
};

int main(int argc, char **argv) 
{
    //API version
    //version();
    
    int option;

    settings Settings;

    std::vector < MenuItem > items {
        { "Bill Acceptor", new Action_A () },
        { "Printer", new Action_B () },
        { "Card Reader", new Action_C () },
        { "RFID", new Action_D () },
    };

    MyMenu Menu(items);
    Action_A ActionA;
    Action_B ActionB;
    Action_C ActionC;
    Action_D ActionD;

    Menu.printMenu();

    std::cin >> option;

    switch (option){
        case 0:
            ActionA.Run();
            break;
        case 1:
            ActionB.Run();
            break;
        case 2:
            ActionC.Run();
            break;
        case 3:
            ActionD.Run();
            break;
        default:
            std::cout << "You didn't tip any option" << std::endl;
    }

    std::cout << "type:" << Settings.type << std::endl;
    return 0;
}

/*void version()
{
  std::cout << "Welcome to verison:  "
    << SAMPLE_VERSION_MAJOR <<
    "." << SAMPLE_VERSION_MINOR <<
    "." << SAMPLE_VERSION_PATCH << std::endl;
}*/