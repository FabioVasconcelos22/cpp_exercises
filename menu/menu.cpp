#include <iostream>
#include <string>
#include <vector>
#include <stack>

namespace Tester {

    //Configuration
    struct settings
    {
    public:
        std::string type = "";
        std::string model = "";
        std::string path = "";
        std::string country = "";
    } config;

    enum class ErrorType : uint8_t {
        InvalidOption = 0
    };

    struct MenuException {
        ErrorType Type;
        std::string Message;
    };
    
    class IAction {
    public:
        virtual void Run () = 0;
    };

    
    struct MenuItem {
        std::string Text;
        IAction *   Action;
    };

    class TerminalMenu {
    private:
        std::vector <MenuItem>  _menuItems;

    public:        
        TerminalMenu(std::vector <MenuItem> const & menuItems) :
            _menuItems (menuItems)
        {}

        void printMenu() const
        {
            for(int i=0; i< _menuItems.size(); i++)
            {
                std::cout << i << " - " << _menuItems.at(i).Text << std::endl;
            }   
        }

        bool runMenuItem (int input) {
            
            // Validate input
            if (input > _menuItems.size()-1) {
                throw MenuException { ErrorType::InvalidOption,"Try another option" };
            }

            //Run input
            _menuItems.at(input).Action->Run();

            
            return true;
        }
    };

    std::stack <TerminalMenu> MenuObject;

    class Act_BillAcceptor : public IAction {
    public:
        void Run () override {
            config.type = "Bill_Acceptor";
            //Preciso de tipo de aceitador, país e path
        }
    };

    class Act_Printer : public IAction {
    public:
        void Run () override {
            config.type = "Printer";
            //Preciso de tipo de impressora e path
        }
    };

    class Act_CardReader : public IAction {
    public:
        void Run () override {
            config.type = "Card_Reader";
            //Preciso de tipo de cardreader e path
        }
    };

    class Act_RFID : public IAction {
    public:
        void Run () override {
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

    TerminalMenu const MainMenu ({
        { "Bill Acceptor", new Act_BillAcceptor () },
        { "Printer", new Act_Printer () },
        { "Card Reader", new Act_CardReader () },
        { "RFID", new Act_RFID () },
        { "Exit", new ExitAction () }
    });
 
    class Act_Enable : public IAction {
    public:
        void Run () override {
            std::cout << "ENABLE" << std::endl;
        }
    };

    class Act_Disable : public IAction {
    public:
        void Run () override {
            std::cout << "DISABLE" << std::endl;
        }
    };

    class Act_Accept : public IAction {
    public:
        void Run () override {
            std::cout << "ACCEPT" << std::endl;
        }
    };

    class BackAction : public IAction {
    public:
        void Run () override {
            MenuObject.pop();
            std::cout << "Back" << std::endl;
        }
    };

    TerminalMenu const BillAcceptorMenu ({
        { "Enable Bill", new Act_Enable () },
        { "Disable Bill", new Act_Disable () },
        { "Accept Bill", new Act_Accept () },
        { "Back", new BackAction () }
    });

    TerminalMenu const PrinterMenu ({
        { "Enable Printer", new Act_Enable () },
        { "Disable Printer", new Act_Disable () },
        { "Accept Printer", new Act_Accept () },
        { "Back", new BackAction () }
    });

    TerminalMenu const CardReaderMenu ({
        { "Enable Card", new Act_Enable () },
        { "Disable Card", new Act_Disable () },
        { "Accept Card", new Act_Accept () },
        { "Back", new BackAction () }
    });

    TerminalMenu const RFIDMenu ({
        { "Enable RFID", new Act_Enable () },
        { "Disable RFID", new Act_Disable () },
        { "Accept RFID", new Act_Accept () },
        { "Back", new BackAction () }
    });
}

//#include "version.h"
//void version();

int main(int argc, char **argv)
{   
    int option;

    Tester::MenuObject.push(Tester::MainMenu);

    try {
        for (;;) {
            Tester::MenuObject.top().printMenu();
            std::cin >> option;
            Tester::MenuObject.top().runMenuItem (option);
            std::cout << "Type: " << Tester::config.type << std::endl;
        }
    } catch(Tester::MenuException & e) {
        std::cerr
            << "\nError type: " << static_cast < int > (e.Type) << ". \n"
            << "Error Message: " << e.Message << "\n" << std::endl;
    }    
    return 0; 
}