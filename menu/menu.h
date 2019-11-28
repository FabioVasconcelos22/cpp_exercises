#pragma once
#ifndef _menu_h_
#define _menu_h_

#include <iostream>
#include <string>
#include <vector>
#include <stack>

namespace Tester {

    struct Settings
    {
    public:
        std::string Type = "";
        std::string Path = "";
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
        Act_BillAcceptor(Settings& config):
            _config (config) 
        {}

        void Run () override {
            _config.Type = "Bill_Acceptor";
            _config.Path = "path do aceitador";

            MenuObject.push(BillAcceptorMenu);
        }
    private:
        Settings& _config;
    };

    TerminalPage const PrinterMenu ({
        { "Enable Printer", new Act_Enable () },
        { "Disable Printer", new Act_Disable () },
        { "Accept Printer", new Act_Accept () },
        { "Back", new BackAction () }
    });

    class Act_Printer : public IAction {
    public:
        Act_Printer (Settings& config): 
            _config (config)
        {}

        void Run () override {
            _config.Type = "Printer";
            _config.Path = "path da printer";
            
            MenuObject.push(PrinterMenu);
        }

    private:
        Settings& _config;
    };

    TerminalPage const CardReaderMenu ({
        { "Enable Card", new Act_Enable () },
        { "Disable Card", new Act_Disable () },
        { "Accept Card", new Act_Accept () },
        { "Back", new BackAction () }
    });
    
    class Act_CardReader : public IAction {
    public:
        Act_CardReader(Settings& config):
            _config (config)
        {}

        void Run () override {
            _config.Type = "Card Reader";
            _config.Path = "path do card reader";
            
            MenuObject.push(CardReaderMenu);
        }
    
    private:
        Settings& _config;
    };

    TerminalPage const RFIDMenu ({
        { "Enable RFID", new Act_Enable () },
        { "Disable RFID", new Act_Disable () },
        { "Accept RFID", new Act_Accept () },
        { "Back", new BackAction () }
    });

    class Act_RFID : public IAction {
    public:
        Act_RFID(Settings& config):
            _config (config)
            {}

        void Run () override {
            _config.Type = "RFID";
            _config.Path = "path do rfid";
            
            MenuObject.push(CardReaderMenu);
        }
    private:
        Settings& _config;
    };

    class ExitAction : public IAction {
    public:
        void Run () override {
            std::cout << "Bye Bye" << std::endl;
            std::exit(0);
        }
    };
}

#endif