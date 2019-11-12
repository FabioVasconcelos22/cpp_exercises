#include <iostream>
#include <string>
#include <vector>

namespace Tester {

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

    TerminalMenu const BillAcceptorMenu ({
        { "A", new A () },
        { "B", new B () },
        { "C", new C () },
        { "Back", new BackAction () }
    });

    TerminalMenu const BillAcceptorMenu ({
        { "A", new A () },
        { "B", new B () },
        { "C", new C () },
        { "Back", new BackAction () }
    });
}

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

int main(int argc, char **argv)
{    
    int option;

    try {
        for (;;) {
            Tester::TerminalMenu.printMenu();
            std::cin >> option;
            Tester::TerminalMenu.runMenuItem (option);
        }
    } catch(Tester::MenuException & e) {
        std::cerr
            << "\nError type: " << static_cast < int > (e.Type) << ". \n"
            << "Error Message: " << e.Message << "\n" << std::endl;
    }

   std::cout << "Type: " << config.type << std::endl;
    
    return 0; 
}