#ifndef boiler_h
#define boiler_h

#include <string>

enum class BoilerType {
    Makefile,
    CMake,
    Unknown
};

enum class BoilerLanguage {
    Cpp,
    C,
    Unknown
};

class Boiler {
public:
    Boiler() = default;
    Boiler(const std::string& name, BoilerType type, BoilerLanguage language) : name_(name), type_(type), language_(language) {};
    std::string name() const {
        return name_;
    }
    void setName(const std::string& name) {
        name_ = name;
    }
    BoilerType type() const {
        return type_;
    }
    void setType(BoilerType type) {
        type_ = type;
    }
    BoilerLanguage language() const {
        return language_;
    }
    void setLanguage(BoilerLanguage language) {
        language_ = language;
    }
private:
    std::string name_;
    BoilerType type_;
    BoilerLanguage language_;
};

#endif