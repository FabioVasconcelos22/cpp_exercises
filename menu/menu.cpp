#include "menu.h"

//#include "version.h"
//void version();

int main(int argc, char **argv)
{  
    using namespace Tester;

    int option = 0;

    Settings configuration;

    TerminalPage const MainMenu ({
        { "Bill Acceptor", new Act_BillAcceptor (configuration) },
        { "Printer", new Act_Printer (configuration) },
        { "Card Reader", new Act_CardReader (configuration) },
        { "RFID", new Act_RFID (configuration) },
        { "Exit", new ExitAction () }
    });
 
    MenuObject.push(MainMenu);

    try {
        for (;;) {
            MenuObject.top().printMenu();
            std::cin >> option;
            MenuObject.top().runMenuItem (option);
            std::cout << "Type: " << configuration.Type << std::endl;
            std::cout << "Path: " << configuration.Path << std::endl;
        }
    } catch(MenuException& e) {
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