#ifndef BLACKBOARDSERVER_H
#define BLACKBOARDSERVER_H

#include <BlackBoardCmd.h>
#include <blackboard.h>
#include <yarp/os/RFModule.h>



class BlackBoardServer : public BlackBoardCmd, public yarp::os::RFModule
{
public:
    BlackBoardServer();
    virtual void SetI16(const std::string& name, const int16_t data);
    virtual void SetI32(const std::string& name, const int32_t data);
    virtual void SetI64(const std::string& name, const YARP_INT64 data);
    virtual void SetByte(const std::string& name, const int8_t data);
    virtual void SetDouble(const std::string& name, const double data);
    virtual void SetBool(const std::string& name, const double data);
    virtual void SetString(const std::string& name, const std::string& data);
    virtual int16_t GetI16(const std::string& name);
    virtual int32_t GetI32(const std::string& name);
    virtual YARP_INT64 GetI64(const std::string& name);
    virtual int8_t GetByte(const std::string& name);
    virtual double GetDouble(const std::string& name);
    virtual bool GetBool(const std::string& name);
    virtual std::string GetString(const std::string& name);


    bool attach(yarp::os::Port &source);
    bool configure( yarp::os::ResourceFinder &rf );
    bool updateModule();
    bool close();


private:
    BlackBoard* content_;
    yarp::os::Port cmd_port_;

};


#endif // BLACKBOARDSERVER_H
