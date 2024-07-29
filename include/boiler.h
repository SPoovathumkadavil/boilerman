#ifndef boiler_h
#define boiler_h

#include <string>

class Boiler
{
public:
    Boiler() = default;
    Boiler(const std::string &name, const std::string &desc, std::string type, std::string language) : name_(name), description_(desc), type_(type), language_(language) {};
    std::string name() const
    {
        return name_;
    }
    void setName(const std::string &name)
    {
        name_ = name;
    }
    std::string description() const
    {
        return description_;
    }
    void setDescription(const std::string &desc)
    {
        description_ = desc;
    }
    std::string type() const
    {
        return type_;
    }
    void setType(std::string type)
    {
        type_ = type;
    }
    std::string language() const
    {
        return language_;
    }
    void setLanguage(std::string language)
    {
        language_ = language;
    }

private:
    std::string name_;
    std::string description_;
    std::string type_;
    std::string language_;
};

#endif