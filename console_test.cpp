#include "console.hpp"
#include <gtest/gtest.h>

TEST(myFunctions, myTest) 
{

}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}