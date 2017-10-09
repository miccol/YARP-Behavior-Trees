#include <iostream>
#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <btyarpmodule.h>


class MyAction : public BTYARPAction
{
public:
    MyAction(std::string name) : BTYARPAction(name)
    {

    }
    int tick()
    {
        std::cout << "Ticking" << std::endl;
        return 1;
    }

    void halt()
    {
        std::cout << "Halting" << std::endl;

    }

};




int main(int argc, char * argv[])
{
    /* initialize yarp network */
    yarp::os::Network yarp;
    /* create your module */
        MyAction module("WalkingModule");
//    /* prepare and configure the resource finder */
    yarp::os::ResourceFinder rf;
    rf.configure(argc, argv);
//    rf.setVerbose(true);
//    cout << "Configuring and starting module. \n";
    module.runModule(rf);   // This calls configure(rf) and, upon success, the module execution begins with a call to updateModule()
//    cout<<"Main returning..."<<endl;
    return 0;
}
