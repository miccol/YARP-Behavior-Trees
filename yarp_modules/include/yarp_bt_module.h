#ifndef YARPBTModule_H
#define YARPBTModule_H
#include "BTCmd.h"

#include "yarp/os/RFModule.h"
#include "yarp/os/Port.h"

#include <mutex>

class YARPBTModule : public BTCmd, public yarp::os::RFModule
{
public:
    YARPBTModule(std::string name);
    bool attach(yarp::os::Port &source);
    bool configure( yarp::os::ResourceFinder &rf );
    bool updateModule();
    bool close();

    int32_t request_tick();
    int32_t request_status();
    void request_halt();


    virtual int tick() = 0;
    virtual void halt() = 0;


    bool is_halted();
    void set_is_halted(bool is_halted);

private:
    yarp::os::Port cmd_port_;
    std::string module_name_;
    bool is_halted_;
    std::mutex is_halted_mutex_;
};


class BTYARPAction : public YARPBTModule
{
public:
    BTYARPAction(std::string name) : YARPBTModule(name)   {}
    virtual int tick() = 0;

    virtual void halt() = 0;

};

class BTYARPCondition : public YARPBTModule
{
public:
    BTYARPCondition(std::string name) : YARPBTModule(name) {}
    virtual int tick() = 0;

    void halt()
    {

    }

};



#endif // YARPBTModule_H
