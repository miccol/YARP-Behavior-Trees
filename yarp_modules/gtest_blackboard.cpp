#include <black_board.h>
#include <iostream>
#include <stdio.h>
#include <rtf/TestCase.h>
#include <rtf/TestResult.h>
#include <rtf/TestResultCollector.h>
#include <rtf/ConsoleListener.h>
#include <rtf/TestAssert.h>

using namespace RTF;

class BlackBoardTest : public TestCase {
public:
    BlackBoardTest() : TestCase("MyTest") {

    }

    virtual ~BlackBoardTest() { }

    virtual bool setup(int argc, char **argv) {
//        RTF_TEST_REPORT("running MyTest::setup...");
        return true;
    }

    virtual void tearDown() {
//        RTF_TEST_REPORT("running MyTest::teardown...");
//        RTF_ASSERT_ERROR("this is just for example!");
    }

    virtual void run() {
        BlackBoard* bb = new BlackBoard();

        bb->SetValue<int>("x", "int", 10);
        int x = bb->GetInt("x");
        RTF_TEST_CHECK(x==10, "int set and get correctly");

        bb->SetValue<int16_t>("x16", "i16", 10);
        int16_t x16 = bb->GetI16("x16");
        RTF_TEST_CHECK(x16==10, "int16 set and get correctly");

        bb->SetValue<int32_t>("x32", "i32", 10);
        int32_t x32 = bb->GetI32("x32");
        RTF_TEST_CHECK(x32==10, "int32 set and get correctly");

        bb->SetValue<int64_t>("x64", "i64", 10);
        int64_t x64 = bb->GetI64("x64");
        RTF_TEST_CHECK(x64==10, "int64 set and get correctly");

        bb->SetValue<double>("d", "double", 1.5);
        double d = bb->GetDouble("d");
        RTF_TEST_CHECK(d==1.5, "double set and get correctly");

        bb->SetValue<bool>("b", "bool", true);
        bool b = bb->GetBool("b");
        RTF_TEST_CHECK(b, "bool set and get correctly");

        bb->SetValue<std::string>("s", "string", "test");
        std::string s = bb->GetString("s");
        RTF_TEST_CHECK(s=="test", "string set and get correctly");

        bb->SetValue<int8_t>("y", "byte", 1);
        int8_t y = bb->GetByte("y");
        RTF_TEST_CHECK(y==1, "byte set and get correctly");

        try
        {
            bb->GetDouble("x");
        }
        catch( const std::exception & ex ) {
            std::string exception_received = ex.what();
            std::string exception_expected = "Cannot find variable x with type double";
            RTF_TEST_CHECK(exception_expected.compare(exception_received) == 0 , "Exception int to double handled correcly.");
        }
    }
};

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
