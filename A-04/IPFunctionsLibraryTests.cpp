#include "gtest/gtest.h"
#include "IPFunctionsLibrary.h"
#include <array>
#include <deque>
#include <list>

TEST(TestIPToStringConversion, TestIPAsIntegral) 
{
    EXPECT_EQ(ConvertIPToString(char(27)), std::string("27"));
    EXPECT_EQ(ConvertIPToString((unsigned char) 176), std::string("176"));
    EXPECT_EQ(ConvertIPToString(short(0)), std::string("0.0"));
    EXPECT_EQ(ConvertIPToString(short(267)), std::string("1.11"));
    EXPECT_EQ(ConvertIPToString(int(882917366)), std::string("52.160.63.246"));
    EXPECT_EQ(ConvertIPToString((unsigned int) 2869173753), std::string("171.4.29.249"));
    EXPECT_EQ(ConvertIPToString(2130706433LL), std::string("0.0.0.0.127.0.0.1"));
    EXPECT_EQ(ConvertIPToString(1237859348273829484), std::string("17.45.194.132.207.194.22.108"));
}

TEST(TestIPToStringConversion, TestIPAsSequenceContainer) 
{
    std::deque<char> IPAsDeque {127, 0, 0, 1};
    std::array<short, 4> IPAsArray {127, 0, 0, 1};
    std::list<int> IPAsList {127, 0, 0, 1};
    std::vector<long> IPAsVector {127, 0, 0, 1};
    
    EXPECT_EQ(ConvertIPToString(IPAsDeque), std::string("127..0..0..1"));
    EXPECT_EQ(ConvertIPToString(IPAsArray), std::string("127..0..0..1"));
    EXPECT_EQ(ConvertIPToString(IPAsList), std::string("127..0..0..1"));
    EXPECT_EQ(ConvertIPToString(IPAsVector), std::string("127..0..0..1"));
}

TEST(TestIPToStringConversion, TestIPAsString) 
{
    std::string IP = "127.0.0.1";
    EXPECT_EQ(ConvertIPToString(IP), std::string("127.0.0.1"));
}

TEST(TestTypesForHomogeneity, ) 
{ 
    EXPECT_EQ(AreHomogeneousTypes<int>(), true);
    EXPECT_EQ((AreHomogeneousTypes<int, int>()), true);
    EXPECT_EQ((AreHomogeneousTypes<int, unsigned int>()), false);
    EXPECT_EQ((AreHomogeneousTypes<float, float, float>()), true);
    EXPECT_EQ((AreHomogeneousTypes<float, double>()), false);
    EXPECT_EQ((AreHomogeneousTypes<int, long>()), false);
    EXPECT_EQ((AreHomogeneousTypes<long, long, long, long, long, long, long>()), true);
    EXPECT_EQ((AreHomogeneousTypes<char, const char>()), false);
    EXPECT_EQ((AreHomogeneousTypes<std::vector<float>, std::list<float>>()), false);
    EXPECT_EQ((AreHomogeneousTypes<std::vector<long>, std::vector<long>>()), true);
}

TEST(TestIPToStringConversion, TestIPAsTuple) 
{
    std::tuple<int> FirstTuple {255};
    std::tuple<unsigned int, unsigned int> SecondTuple {255, 0};
    std::tuple<int, int, int, int> ThirdTuple {10, 50, 0, 29};
    std::tuple<long, long, long, long, long, long, long, long> FourthTuple {15, 0, 62, 245, 54, 28, 18, 23};

    EXPECT_EQ(ConvertIPToString(FirstTuple), std::string("255"));
    EXPECT_EQ(ConvertIPToString(SecondTuple), std::string("255..0"));
    EXPECT_EQ(ConvertIPToString(ThirdTuple), std::string("10..50..0..29"));
    EXPECT_EQ(ConvertIPToString(FourthTuple), std::string("15..0..62..245..54..28..18..23"));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}