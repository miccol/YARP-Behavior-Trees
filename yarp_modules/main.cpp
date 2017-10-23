#include <iostream>
#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <btyarpmodule.h>
#include <black_board.h>

class MyAction : public BTYARPAction
{
public:
    MyAction(std::string name) : BTYARPAction(name)
    {

    }
    int tick()
    {
        std::cout << "Ticking" << std::endl;
        return 0;
    }

    void halt()
    {
        std::cout << "Halting" << std::endl;

    }

};




int main(int argc, char * argv[])
{
//    /* initialize yarp network */
//    yarp::os::Network yarp;
//    /* create your module */
//    MyAction module("WalkingModule");
//    yarp::os::ResourceFinder rf;
//    rf.configure(argc, argv);
//    module.runModule(rf);

    BlackBoard* bb = new BlackBoard();

    bb->SetValue<int>("x", "int", 10);
    bb->SetNew<bool>("y", "bool", true);

    bb->PrintBlackBoard();

    bb->SetValue<int>("x", "int", 15);

    bb->PrintBlackBoard();

    try
    {
        std::string x = bb->GetString("x");
        std::cout << "The value of x is "<< x << std::endl;
        std::cout << "DONE!" << std::endl;
    }
    catch( const std::exception & ex ) {
        std::cerr << ex.what() << std::endl;
    }



    return 0;
}
