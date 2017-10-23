#ifndef PROPERTY_H
#define PROPERTY_H
#include<string>

class Property
{

public:
    Property(const std::string& name, const std::string& type) //note: we don't lightly copy strings in C++
      : m_name(name) ,m_type(type) {}
    virtual ~Property() {}

    std::string name() const
    {
        return m_name;
    }

    std::string type() const
    {
        return m_type;
    }

private:
    std::string m_name;
    std::string m_type;
};

#endif // PROPERTY_H
