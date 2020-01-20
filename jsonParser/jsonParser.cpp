#include <iostream>
#include <fstream>
#include <vector>
#include "ExternalLibs/json.hpp"

using json = nlohmann::json;

struct Config {
    std::string Name;
    std::string LastName;
    int Age;
};

Config const Default { "Fábio", "Vasconcelos", 27};

std::vector <std::string> Invalid;

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


void PrintConfigs(Config const& config) {
    std::cout << "Name: " << config.Name << std::endl;
    std::cout << "Last Name: " << config.LastName << std::endl;
    std::cout << "Age: " << config.Age << std::endl;
}

void PrintMissings(std::vector<std::string> Missings) {
    std::cout << "Missing configs: " << std::endl;
    for (auto i : Missings) {
        std::cout << "  -> " << i << std::endl;
    }
}

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

    //Check if config json exist
    std::ifstream ifs("/home/fabiov/workspace/Scripts/jsonParser/config.json");

    if (ifs.is_open()) { //Reconfigure from file
        //Parse config json file
        json const j = json::parse(ifs);

        //Fill config here
        ParseConfig(j, "Name", config.Name);
        ParseConfig(j, "LastName", config.LastName);
        ParseConfig(j, "Age", config.Age);
    }

    //Validate Config
    if(!ValidateConfig(config)){
        return 0;
    }

    return 0;
}