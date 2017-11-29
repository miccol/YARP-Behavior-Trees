#include "blackboard.h"
#include <iostream>

BlackBoard::BlackBoard()
{

}

void BlackBoard::PrintBlackBoard()
{
    std::cout << content_2.toString() << std::endl;
}


int BlackBoard::GetInt(std::string name)
{

    yarp::os::Value value =content_2.find(name);

    if (value.isNull())
    {
        std::string error_message = "Cannot find variable " + name + " with type int";
        throw std::invalid_argument(error_message.c_str());
    }

    return value.asInt();
}

int16_t BlackBoard::GetI16(std::string name)
{

    yarp::os::Value value =content_2.find(name);

    if (value.isNull())
    {
        std::string error_message = "Cannot find variable " + name + " with type i16";
        throw std::invalid_argument(error_message.c_str());
    }

    return value.asInt();
}


int32_t BlackBoard::GetI32(std::string name)
{
    yarp::os::Value value =content_2.find(name);

    if (value.isNull())
    {
        std::string error_message = "Cannot find variable " + name + " with type i32";
        throw std::invalid_argument(error_message.c_str());
    }

    return value.asInt();
}


int64_t BlackBoard::GetI64(std::string name)
{
    yarp::os::Value value =content_2.find(name);

    if (value.isNull())
    {
        std::string error_message = "Cannot find variable " + name + " with type i64";
        throw std::invalid_argument(error_message.c_str());
    }

    return value.asInt64();
}

int8_t BlackBoard::GetByte(std::string name)
{
    yarp::os::Value value =content_2.find(name);

    if (value.isNull())
    {
        std::string error_message = "Cannot find variable " + name + " with type byte";
        throw std::invalid_argument(error_message.c_str());
    }

    return value.asInt();
}

bool BlackBoard::GetBool(std::string name)
{

    yarp::os::Value value =content_2.find(name);

    if (value.isNull())
    {
        std::string error_message = "Cannot find variable " + name + " with type bool";
        throw std::invalid_argument(error_message.c_str());
    }

    return value.asBool();
}


double_t BlackBoard::GetDouble(std::string name)
{
    yarp::os::Value value =content_2.find(name);

    if (value.isNull())
    {
        std::string error_message = "Cannot find variable " + name + " with type double";
        throw std::invalid_argument(error_message.c_str());
    }

    return value.asDouble();

}

std::string BlackBoard::GetString(std::string name)
{
    yarp::os::Value value =content_2.find(name);

    if (value.isNull())
    {
        std::string error_message = "Cannot find variable " + name + " with type string";
        throw std::runtime_error(error_message.c_str());
    }

    return value.asString();

}


