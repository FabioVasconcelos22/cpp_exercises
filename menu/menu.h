#pragma once
#ifndef _menu_h_
#define _menu_h_

#include <iostream>
#include <string>
#include <vector>
#include <stack>

namespace Tester {

    struct settings
    {
    public:
        std::string type = "";
        std::string model = "";
        std::string path = "";
        std::string country = "";

        void ThrowError();

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
        TerminalMenu(std::vector <MenuItem> const & menuItems);

        void printMenu() const;

        bool runMenuItem (int input);
    };

    std::stack <TerminalMenu> MenuObject;
    
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

    class Act_BillAcceptor : public IAction {
    public:
        void Run () override {
            config.type = "Bill_Acceptor";
            MenuObject.push(BillAcceptorMenu);
        }
    };

    TerminalMenu const PrinterMenu ({
        { "Enable Printer", new Act_Enable () },
        { "Disable Printer", new Act_Disable () },
        { "Accept Printer", new Act_Accept () },
        { "Back", new BackAction () }
    });

    class Act_Printer : public IAction {
    public:
        void Run () override {
            config.type = "Printer";
            MenuObject.push(PrinterMenu);
        }
    };

    TerminalMenu const CardReaderMenu ({
        { "Enable Card", new Act_Enable () },
        { "Disable Card", new Act_Disable () },
        { "Accept Card", new Act_Accept () },
        { "Back", new BackAction () }
    });
    
    class Act_CardReader : public IAction {
    public:
        void Run () override {
            config.type = "Card_Reader";
            MenuObject.push(CardReaderMenu);
        }
    };

    TerminalMenu const RFIDMenu ({
        { "Enable RFID", new Act_Enable () },
        { "Disable RFID", new Act_Disable () },
        { "Accept RFID", new Act_Accept () },
        { "Back", new BackAction () }
    });

    class Act_RFID : public IAction {
    public:
        void Run () override {
            config.type = "RFID";
            MenuObject.push(CardReaderMenu);
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
}

#endif