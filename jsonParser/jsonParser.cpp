#include <iostream>
#include <fstream>
#include <vector>
#include "ExternalLibs/json.hpp"

using nlohmann::json;

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

struct Config {
    std::string Name = "Fábio";
    std::string LastName = "Vasconcelos";
    int Age = 27;
};

class ConfigParserInterface {
public:

    virtual Config Parse(std::istream & source) = 0;

    std::string Error;

    std::vector < std::string > const& GetMissingFields() const {
        return __MissingFields;
    };

protected:
    std::vector < std::string > __MissingFields;

};

//Soft configuration; Check missings to know if you miss some configuration value
class ConfigJsonParser : public ConfigParserInterface {
public:

    Config Parse (std::istream & source) override {

        json j;
        try {
             j = json::parse(source);
        } catch (json::exception &ex) {
            Error = "PARSING ERROR";
            throw Error;
        }

        _Read(j, "Name", _config.Name);
        _Read(j, "LastName", _config.LastName);
        _Read(j, "Age", _config.Age);

        return _config;
    }

private:
    Config _config;

    template < typename _t >
    void _Read(json const& j, std::string const& field, _t& cfg) {

        if (j.find(field)==j.end()) {
            __MissingFields.push_back(field);
        } else {
            j[field].get_to(cfg);
        }
    }
};

int main(int argc, char **argv) {

    Config config;
    ConfigJsonParser ParseConfig;

    std::ifstream ifs("../config.json");

    try {
        config = ParseConfig.Parse(ifs);
    } catch (std::string &ex) {
        std::cout << ex << std::endl;
    }




    if(ParseConfig.GetMissingFields().empty()) {
        std::cout << config.Name << config.LastName << config.Age << std::endl;
    } else {
        for(auto x:ParseConfig.GetMissingFields()) {
            std::cerr << x << std::endl;
        }
    }
    return 0;
}