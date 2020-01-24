#include <iostream>
#include <fstream>
#include <vector>
#include "ExternalLibs/json.hpp"

struct Config {
public:
    std::string Name;
    std::string LastName;
    int Age;

    void Parse (std::istream const & source);

private:

};

Config const Default {
    "Fábio",
    "Vasconcelos",
    27
};


void Config::Parse(std::istream & source) {

    if(source.)

    nlohmann::json const j = nlohmann::json::parse(source);

    Read(cxt, "name", config.Name);
    Read(cxt, "age", config.Age);
    Read(cxt, "lastname", config.LastName);
}

// -- other stuffs by other guy
/*namespace other_stuff {

    struct ReadContext {
        json & source;
        std::vector < std::string > errors;
    };

    template < typename _t >
    inline void Read (ReadContext & cxt, std::string const & name, _t & dest) {
        auto it = cxt.source.find (name);

        if (it != cxt.source.end()) {
            try {
                it->get_to(dest);
            } catch (json::exception & ex) {
                cxt.errors.push_back (std::string (ex.what ()) + " on field " + name);
            }
        } else {
            cxt.errors.push_back ("UUUUUUiiii, fudeu " + name);
        }
    }

    Config ReadConfig (std::istream & stream) {

        auto source = json::parse (stream);

        Config config = Default;

        ReadContext cxt { source };

        // fill here
        Read(cxt, "name", config.Name);
        Read(cxt, "age", config.Age);
        Read(cxt, "lastname", config.LastName);

        if (!cxt.errors.empty ())
            throw std::exception ();

        return config;
    }

}
*/
//------------
/*
Config ParseConfigFile (std::istream const & source); // throws

struct ParseReport {
    std::vector < std::string > Errors;
    std::vector < std::string > Warnings;
};

Config ParseConfigFile (std::istream const & source, ParseReport & report); // does not throw

struct ConfigParser {
public:
    ConfigParser (std::istream const & source);
    Config Parse (); // throws stuffs
};

struct ConfigParser {
public:
    ConfigParser(std::istream const & source);
    Config Parse (); // does not throw
l
    bool HasErrors () const;
    bool HasWarnings () const;

    std::vector < std::string > const & Errors () const;
    std::vector < std::string > const & Warnings () const;
};

struct Config {
public:
    ......


    static Config Parse (std::istream const & source); // throws stuffs

};
//------------

auto cfg = Config::Parse (stream);
*/

bool ValidateConfig(Config const& cfg) {
    if(Invalid.empty())
    {
        PrintConfigs(cfg);
    } else {
        PrintMissings(Invalid);
        return false;
    }
    return true;
}

template < typename _t >
void ParseConfig(json const& j, std::string const& field, _t& cfg) {

    if (j.find(field)==j.end()) {
        Invalid.push_back(field);
    } else {
        j[field].get_to(cfg);
    }
}


int main(int argc, char **argv) {

    Config config = Default;
    std::vector <std::string> Invalid;

    //Check if config json exist
    std::ifstream ifs("../confidg.json");

    if (ifs.is_open()) { //Reconfigure from file
        //Parse config json file
        json const j = json::parse(ifs);

        //Fill config here
        ParseConfig(j, "Name", config.Name);
        ParseConfig(j, "LastName", config.LastName);
        ParseConfig(j, "Age", config.Age);
    } else {
        std::cout << "Config File do not exist." << std::endl;
        std::cout << "Using Default values..." << std::endl;
    }

    //Validate Config
    if(!ValidateConfig(config)){
        return 0;
    }

    return 0;
}