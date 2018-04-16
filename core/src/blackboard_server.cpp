#include "blackboard_server.h"


//TODO add try-catch clause
BlackBoardServer::BlackBoardServer(yarp::os::Property* blackboard_ptr ) : BlackBoardCmd(),yarp::os::RFModule()
{
    // content_ = new BlackBoard();
    blackboard_ptr_ = blackboard_ptr;
}


bool BlackBoardServer::attach(yarp::os::Port &source)
{
    return this->yarp().attachAsServer(source);
}
bool BlackBoardServer::configure( yarp::os::ResourceFinder &rf )
{
    std::string moduleName = rf.check("name",
            yarp::os::Value("BlackBoardServerModule"),
            "module name (string)").asString().c_str();
    setName(moduleName.c_str());
    std::string slash="/";
    attach(cmd_port_);
    std::string cmd_port_name= "/";
    cmd_port_name+= getName();
    cmd_port_name += "/cmd";
    if (!cmd_port_.open(cmd_port_name.c_str())) {
        std::cout << getName() << ": Unable to open port " << cmd_port_name << std::endl;
        return false;
    }
    return true;
}
bool BlackBoardServer::updateModule()
{
    return true;
}
bool BlackBoardServer::close()
{
    cmd_port_.close();
    return true;
}


void BlackBoardServer::SetI16(const std::string &name, const int16_t data)
{
    try
    {
        yarp::os::Value value = data;

        // content_->SetValue(name, "i16", value);
        blackboard_ptr_->put(name,value);
    }
    catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
    }
}

void BlackBoardServer::SetI32(const std::string &name, const int32_t data)
{
    try
    {
        yarp::os::Value value = data;

        // content_->SetValue(name, "i32", value);
        blackboard_ptr_->put(name,value);
    }
    catch( const std::exception & ex )
    {
        std::cout << ex.what() << std::endl;
    }
}

void BlackBoardServer::SetI64(const std::string &name, const YARP_INT64 data)
{    try
     {
        // content_->SetValue(name, "i64", (int)data); //loosing data here but a yarp value does not have .makeInt64()
        blackboard_ptr_->put(name,(int)data);

     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
    }
}

void BlackBoardServer::SetByte(const std::string &name, const int8_t data)
{    try
     {
        // content_->SetValue(name,"byte",data);
        blackboard_ptr_->put(name,data);
     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
    }

}

void BlackBoardServer::SetDouble(const std::string &name, const double data)
{    try
     {
        yarp::os::Value value;
        value.makeDouble(data);
        // content_->SetValue(name,"double",data);
        blackboard_ptr_->put(name,data);

     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
    }

}

void BlackBoardServer::SetBool(const std::string &name, const double data)
{    try
     {
        // content_->SetValue(name, "bool", data);
                blackboard_ptr_->put(name,data);
     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
    }

}

void BlackBoardServer::SetString(const std::string &name, const std::string &data)
{    try
     {
        yarp::os::Value value;
        value.makeString(data);
        // content_->SetValue(name,"string", *value.makeString(data));
                blackboard_ptr_->put(name,data);

     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
    }
}

int16_t BlackBoardServer::GetI16(const std::string &name)
{    try
     {
        // return content_->GetI16(name);
        return blackboard_ptr_->find(name).asInt();
     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}

int32_t BlackBoardServer::GetI32(const std::string &name)
{    try
     {
        return blackboard_ptr_->find(name).asInt();
     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
        return NULL;
    }
}

YARP_INT64 BlackBoardServer::GetI64(const std::string &name)
{    try
     {
        return blackboard_ptr_->find(name).asInt();
     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}

int8_t BlackBoardServer::GetByte(const std::string &name)
{    try
     {
        return blackboard_ptr_->find(name).asInt();
     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}

double BlackBoardServer::GetDouble(const std::string &name)
{    try
     {
        return blackboard_ptr_->find(name).asDouble();
     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
        return -1.0;
    }

}

bool BlackBoardServer::GetBool(const std::string &name)
{    try
     {
        return blackboard_ptr_->find(name).asBool();
     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
        return false;
    }
}


std::string BlackBoardServer::GetString(const std::string &name)
{    try
     {
        return blackboard_ptr_->find(name).asString();
     }
     catch( const std::invalid_argument & ex )
    {
        std::cout << ex.what() << std::endl;
        return "";
    }

}

