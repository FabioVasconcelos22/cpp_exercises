#include "menu.h"

//#include "version.h"
//void version();

int main(int argc, char **argv)
{   
    int option;
    
    Tester::Configuration config;

    Tester::MenuObject.push(Tester::MainMenu);

    try {
        for (;;) {
            Tester::MenuObject.top().printMenu();
            std::cin >> option;
            Tester::MenuObject.top().runMenuItem (option);
            std::cout << "Type: " << config.GetType << std::endl;
            std::cout << "Path: " << config.GetPath << std::endl;
        }
    } catch(Tester::MenuException& e) {
        std::cerr
            << "\nError type: " << static_cast < int > (e.Type) << ". \n"
            << "Error Message: " << e.Message << "\n" << std::endl;
    }    
    return 0; 
}



namespace Tester {
    
    TerminalPage::TerminalPage(std::vector <MenuItem> const & menuItems) :
            _menuItems (menuItems)
            {}

    void TerminalPage::printMenu() const
    {
        for(int i=0; i< _menuItems.size(); i++)
        {
            std::cout << i << " - " << _menuItems.at(i).Text << std::endl;
        } 
    }

    bool TerminalPage::runMenuItem (int input) 
    {            
        // Validate input
        if (input > _menuItems.size()-1) {
            throw MenuException { ErrorType::InvalidOption,"Try another option" };
        }

        //Run input
        _menuItems.at(input).Action->Run();
        
        return true;
    }
}