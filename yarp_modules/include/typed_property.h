#ifndef TYPED_PROPERTY_H
#define TYPED_PROPERTY_H
#include <string>
#include <property.h>
template< typename T >
class TypedProperty : public Property
{
public:
    TypedProperty (const std::string& name,const std::string& type, const T& data) : Property(name, type), m_data(data) {}

    T data() const
    {
        return m_data;
    }
    void set_data(const T& data)
    {
        m_data = data;
    }


private:
    T m_data;
};

typedef std::vector< std::shared_ptr<Property> > property_list_type;

// https://stackoverflow.com/questions/3559412/how-to-store-different-data-types-in-one-list-c
#endif // TYPED_PROPERTY_H
