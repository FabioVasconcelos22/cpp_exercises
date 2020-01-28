#include <iostream>
#include <fstream>
#include <vector>
#include "ExternalLibs/json.hpp"

using nlohmann::json;

struct Config {
    std::string Name = "Fábio";
    std::string LastName = "Vasconcelos";
    int Age = 27;
};

class ConfigParserInterface {
public:

    virtual Config Parse(std::istream & source) = 0;

    std::vector < std::string > const& GetErrors() const {
        return __Errors;
    };

    std::vector < std::string > const& GetMissingFields() const {
        return __MissingFields;
    };

    bool hasWarnings() {
        return !__MissingFields.empty();
    }

    bool hasError() {
        return !__Errors.empty();
    }

protected:

    std::vector <std::string> __Errors;
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
            __Errors.push_back (ex.what());
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

    ConfigJsonParser ParseConfig;
    std::ifstream ifs("../config.json");
    Config config = ParseConfig.Parse(ifs);;
    
    return 0;
}