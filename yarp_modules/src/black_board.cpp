#include "black_board.h"
#include <iostream>

BlackBoard::BlackBoard()
{

}

void BlackBoard::PrintBlackBoard()
{
    for(std::shared_ptr<Property> p : content_)
    {
        std::string name = p.get()->name();
        Property* ptr = p.get();
        std::string type = ptr->type();

        if (type == "int")
        {
            int value = ((TypedProperty<int>*)ptr)->data();
            std::cout << name << " Has Value " << value <<std::endl;
        }
        else if  (type == "byte")
        {
            int8_t value = ((TypedProperty<int8_t>*)ptr)->data();
            std::cout << name << " Has Value "  << value <<std::endl;
        }
        else if  (type == "i16")
        {
            int16_t value = ((TypedProperty<int16_t>*)ptr)->data();
            std::cout << name << " Has Value " << value <<std::endl;
        }
        else if  (type == "i32")
        {
            int32_t value = ((TypedProperty<int32_t>*)ptr)->data();
            std::cout << name << " Has Value " << value <<std::endl;
        }
        else if  (type == "i64")
        {
            int64_t value = ((TypedProperty<int64_t>*)ptr)->data();
            std::cout << name << " Has Value " << value <<std::endl;
        }
        else if  (type == "bool")
        {
            bool value = ((TypedProperty<bool>*)ptr)->data();
            std::cout << name << " Has Value " << std::boolalpha << value <<std::endl;
        }
        else if  (type == "double")
        {
            double value = ((TypedProperty<double>*)ptr)->data();
            std::cout << name << " Has Value "  << value <<std::endl;
        }
        else if  (type == "string")
        {
            std::string value = ((TypedProperty<std::string>*)ptr)->data();
            std::cout << name << " Has Value "  << value <<std::endl;
        }
        else
        {
            throw std::invalid_argument("Invalid Type for ");
        }
    }
}


int BlackBoard::GetInt(std::string name)
{
    for(std::shared_ptr<Property> p : content_)
    {
        if ( name == p.get()->name()  && p.get()->type() == "int")
        {
            Property* ptr = p.get();
            return ((TypedProperty<int>*)ptr)->data();
        }
    }
    std::string error_message = "Cannot find variable " + name + "with type int";
    throw std::invalid_argument(error_message.c_str());
}

int16_t BlackBoard::GetI16(std::string name)
{
    for(std::shared_ptr<Property> p : content_)
    {
        if ( name == p.get()->name()  && p.get()->type() == "i16")
        {
            Property* ptr = p.get();
            return ((TypedProperty<int16_t>*)ptr)->data();
        }
    }
    std::string error_message = "Cannot find variable " + name + "with type i16";
    throw std::invalid_argument(error_message.c_str());
}


int32_t BlackBoard::GetI32(std::string name)
{
    for(std::shared_ptr<Property> p : content_)
    {
        if ( name == p.get()->name()  && p.get()->type() == "i32")
        {
            Property* ptr = p.get();
            return ((TypedProperty<int32_t>*)ptr)->data();
        }
    }
    std::string error_message = "Cannot find variable " + name + "with type i32";
    throw std::invalid_argument(error_message.c_str());
}


int64_t BlackBoard::GetI64(std::string name)
{
    for(std::shared_ptr<Property> p : content_)
    {
        if ( name == p.get()->name()  && p.get()->type() == "i64")
        {
            Property* ptr = p.get();
            return ((TypedProperty<int64_t>*)ptr)->data();
        }
    }
    std::string error_message = "Cannot find variable " + name + "with type i64";
    throw std::invalid_argument(error_message.c_str());
}

int8_t BlackBoard::GetByte(std::string name)
{
    for(std::shared_ptr<Property> p : content_)
    {
        if ( name == p.get()->name() && p.get()->type() == "byte")
        {
            Property* ptr = p.get();
            return ((TypedProperty<int8_t>*)ptr)->data();
        }
    }
    std::string error_message = "Cannot find variable " + name + "with type byte";
    throw std::invalid_argument(error_message.c_str());
}

bool BlackBoard::GetBool(std::string name)
{
    for(std::shared_ptr<Property> p : content_)
    {
        if ( name == p.get()->name() && p.get()->type() == "bool")
        {
            Property* ptr = p.get();
            return ((TypedProperty<bool>*)ptr)->data();
        }
    }
    std::string error_message = "Cannot find variable " + name + "with type bool";
    throw std::invalid_argument(error_message.c_str());
}


double BlackBoard::GetDouble(std::string name)
{
    for(std::shared_ptr<Property> p : content_)
    {
        if ( name == p.get()->name() && p.get()->type() == "double")
        {
            Property* ptr = p.get();
            return ((TypedProperty<double>*)ptr)->data();
        }
    }
    std::string error_message = "Cannot find variable " + name + "with type double";
    throw std::invalid_argument(error_message.c_str());
}


std::string BlackBoard::GetString(std::string name)
{
    for(std::shared_ptr<Property> p : content_)
    {
        if ( name == p.get()->name() && p.get()->type() == "string")
        {
            Property* ptr = p.get();
            return ((TypedProperty<std::string>*)ptr)->data();
        }
    }
    std::string error_message = "Cannot find variable " + name + " with type string";
    throw std::runtime_error(error_message.c_str());
}


