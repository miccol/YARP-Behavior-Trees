#include <gtest/gtest.h>
#include <black_board.h>


struct BlackboardTest : testing::Test
{
    BlackBoard* bb = new BlackBoard();

 //    bb->SetValue<int>("x", "int", 10);
//    bb->SetNew<bool>("y", "bool", true);

//    bb->PrintBlackBoard();

//    bb->SetValue<int>("x", "int", 15);

//    bb->PrintBlackBoard();

//    try
//    {
//        std::string x = bb->GetString("x");
//        std::cout << "The value of x is "<< x << std::endl;
//        std::cout << "DONE!" << std::endl;
//    }
//    catch( const std::exception & ex ) {
//        std::cerr << ex.what() << std::endl;
//    }

};


/****************TESTS START HERE***************************/



TEST_F(BlackboardTest, WriteandRead)
{

    bb->SetValue<int>("x", "int", 10);
    int value = bb->GetInt("x");
    ASSERT_EQ(10, value);

}




int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
