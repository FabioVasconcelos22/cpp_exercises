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
        std::string path = "";
    };

    class Configuration {
    private:
        static settings _config;
    public:         
        void SetType (std::string config) {
            _config.type = config;
        }

        void SetPath (std::string config) {
            _config.path = config;
        }

        std::string GetType () {
            return _config.type;
        }

        std::string GetPath () {
            return _config.path;
        }

        settings GetConfig (){
            return _config;
        }
    };

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
        Configuration config;
    };   

    struct MenuItem {
        std::string Text;
        IAction *   Action;
    };

    class TerminalPage {
    private:
        std::vector <MenuItem>  _menuItems;

    public:        
        TerminalPage(std::vector <MenuItem> const & menuItems);

        void printMenu() const;

        bool runMenuItem (int input);
    };

    std::stack <TerminalPage> MenuObject;
    
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
    
    TerminalPage const BillAcceptorMenu ({
        { "Enable Bill", new Act_Enable () },
        { "Disable Bill", new Act_Disable () },
        { "Accept Bill", new Act_Accept () },
        { "Back", new BackAction () }
    });

    class Act_BillAcceptor : public IAction {
    public:
        void Run () override {
            config.SetType ("Bill_Acceptor");
            config.SetPath ("path do aceitador");
            MenuObject.push(BillAcceptorMenu);
        }
    };

    TerminalPage const PrinterMenu ({
        { "Enable Printer", new Act_Enable () },
        { "Disable Printer", new Act_Disable () },
        { "Accept Printer", new Act_Accept () },
        { "Back", new BackAction () }
    });

    class Act_Printer : public IAction {
    public:
        void Run () override {
            config.SetType ("Printer");
            config.SetPath ("path da printer");
            MenuObject.push(PrinterMenu);
        }
    };

    TerminalPage const CardReaderMenu ({
        { "Enable Card", new Act_Enable () },
        { "Disable Card", new Act_Disable () },
        { "Accept Card", new Act_Accept () },
        { "Back", new BackAction () }
    });
    
    class Act_CardReader : public IAction {
    public:
        void Run () override {
            config.SetType ("Card Reader");
            config.SetPath ("path do card reader");
            MenuObject.push(CardReaderMenu);
        }
    };

    TerminalPage const RFIDMenu ({
        { "Enable RFID", new Act_Enable () },
        { "Disable RFID", new Act_Disable () },
        { "Accept RFID", new Act_Accept () },
        { "Back", new BackAction () }
    });

    class Act_RFID : public IAction {
    public:
        void Run () override {
            config.SetType ("RFID");
            config.SetPath ("path do rfid");
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

    TerminalPage const MainMenu ({
        { "Bill Acceptor", new Act_BillAcceptor () },
        { "Printer", new Act_Printer () },
        { "Card Reader", new Act_CardReader () },
        { "RFID", new Act_RFID () },
        { "Exit", new ExitAction () }
    });
}

#endif