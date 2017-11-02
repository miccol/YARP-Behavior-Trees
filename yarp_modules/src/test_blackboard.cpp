#include <blackboard.h>
#include <iostream>
#include <stdio.h>
#include <rtf/TestCase.h>
#include <rtf/TestResult.h>
#include <rtf/TestResultCollector.h>
#include <rtf/ConsoleListener.h>
#include <rtf/TestAssert.h>

using namespace RTF;
#include <rtf/dll/Plugin.h>
#include <rtf/TestAssert.h>

#include <test_blackboard.h>



#include <iostream>
#include <yarp/os/all.h>
#include <BlackBoardCmd.h>
// prepare the plugin
PREPARE_PLUGIN(BlackBoardTest)


BlackBoardTest::BlackBoardTest() : TestCase("MyTest"){ }

BlackBoardTest::~BlackBoardTest() {}

bool BlackBoardTest::setup(int argc, char **argv) {
    //        RTF_TEST_REPORT("running MyTest::setup...");
    return true;
}

void BlackBoardTest::tearDown() { }

    void BlackBoardTest::run()
    {
        using namespace yarp::os;
        yarp::os::Property config;
        Network yarp;
        /* This port will be used to talk to the remote server*/
        Port client_port;
        std::string servername= "/blackboardserver";
        client_port.open("/tests/blackboardclient");
        /* connect to server */
        if (!yarp.connect("/tests/blackboardclient",servername.c_str()))
        {
            std::cout << "Error! Could not connect to server " << servername << std::endl;
            RTF_ASSERT_ERROR("Error! Could not connect to server");
            return ;
        }
        /* Instatate proxy object and attach it to the port -- the proxy will use this port to talk to the server*/
        BlackBoardCmd black_board_cmd;
        black_board_cmd.yarp().attachAsClient(client_port);
        /* Now we are ready to chat with the server! */
        /* Notice that from now on we will invoke only the server methods declared in demo.thrift/Demo.h */

        // Check int(s) set and get


        black_board_cmd.SetI16("x16", 10);
        int16_t x16 = black_board_cmd.GetI16("x16");
        std::cout << "x16 " << x16 << std::endl;
        RTF_TEST_CHECK(x16 == 10, "i16 set and get");

        black_board_cmd.SetI32("x32",10);
        int32_t x32 = black_board_cmd.GetI32("x32");
        RTF_TEST_CHECK(x32 == 10, "i32 set and get");

        black_board_cmd.SetI64("x64",10);
        YARP_INT64 x64 = black_board_cmd.GetI64("x64");
        RTF_TEST_CHECK(x64 == 10, "i64 set and get");

        black_board_cmd.SetDouble("d",1.5);
        double d = black_board_cmd.GetDouble("d");
        RTF_TEST_CHECK(d == 1.5, "double set and get");

        black_board_cmd.SetString("s", "test");
        std::string s = black_board_cmd.GetString("s");
        RTF_TEST_CHECK(s == "test", "string set and get");

        black_board_cmd.SetByte("byte", 1);
        int8_t y = black_board_cmd.GetByte("byte");
        RTF_TEST_CHECK(y == 1, "byte set and get");


        black_board_cmd.SetI32("x32", 11);
        x32 = black_board_cmd.GetByte("x32");
        RTF_TEST_CHECK(x32 == 11, "x32 edit");


    }

int main(int argc, char** argv)
{
    // create a test listener to collect the result
    // and enable the verbose mode
    ConsoleListener listener(true);

    // create a collector to get computer readable
    // test results
    TestResultCollector collector;

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);
    result.addListener(&collector);

    // calling a test case
    BlackBoardTest atest;
    atest.TestCase::run(result);

    // return 0 if the test passed
    // otherwise the number of failed test
    return collector.failedCount();
}




