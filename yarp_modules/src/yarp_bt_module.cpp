#include "yarp_bt_module.h"


YARPBTModule::YARPBTModule(std::string name) : BTCmd(), RFModule()
{
    module_name_ = name;

}

bool YARPBTModule::attach(yarp::os::Port &source)
{
    return this->yarp().attachAsServer(source);
}
bool YARPBTModule::configure( yarp::os::ResourceFinder &rf )
{

    std::string slash="/";
    attach(cmd_port_);
    std::string cmd_port_name = "/";
    cmd_port_name += module_name_;
    cmd_port_name += "/cmd";
    if (!cmd_port_.open(cmd_port_name.c_str())) {
        std::cout << getName() << ": Unable to open port " << cmd_port_name << std::endl;
        return false;
    }
    return true;
}
bool YARPBTModule::updateModule()
{
    return true;
}
bool YARPBTModule::close()
{
    cmd_port_.close();
    return true;
}

void YARPBTModule::request_tick()
{
    set_is_halted(false);
    tick();
    //return 1;
}

int32_t YARPBTModule::request_status()
{
    return 1;
}

void YARPBTModule::request_halt()
{
    set_is_halted(true); // set is_halted BEFORE calling halt(), the halt routine must be the last thing a BT node is doing
    halt();
}

bool YARPBTModule::is_halted()
{
    std::lock_guard<std::mutex> lock(is_halted_mutex_);
    return is_halted_;
}

void YARPBTModule::set_is_halted(bool is_halted)
{
    std::lock_guard<std::mutex> lock(is_halted_mutex_);

    is_halted_ = is_halted;
}
