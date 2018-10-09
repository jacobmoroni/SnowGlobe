#include <gtest/gtest.h>
#include "vector.h"

TEST(GivenSingleVector,whenInializingVectors_MembersAreCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};

    EXPECT_EQ(1.0,vec1.getX());
    EXPECT_EQ(2.0,vec1.getY());
    EXPECT_EQ(3.0,vec1.getZ());
}

TEST(GivenSingleVector, whenInvertingVector_OutputIsCorrect)
{
    phys::Vector vec1{1.0,2.0,3.0};
    phys::Vector goldenVector{-1.0,-2.0,-3.0};
    EXPECT_EQ(goldenVector,-vec1);
}

TEST(Given2Vectors,whenAdding2Vectors_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    phys::Vector vec2{1.0, 2.0, 3.0};
    phys::Vector answerVector{vec1+vec2};
    phys::Vector goldenVector{2.0,4.0,6.0};

    EXPECT_EQ(2.0,answerVector.getX());
    EXPECT_EQ(4.0,answerVector.getY());
    EXPECT_EQ(6.0,answerVector.getZ());
    EXPECT_EQ(goldenVector,vec1+vec2);
}

TEST(Given2Vectors,whenSubtracting2Vectors_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    phys::Vector vec2{3.0, 5.0, 1.0};
    phys::Vector goldenVector{-2.0,-3.0,2.0};

    EXPECT_EQ(goldenVector,vec1-vec2);
}

TEST(GivenVectorAndNumber, whenMultiplyingByNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    double number{0.1};

    phys::Vector goldenVector{0.1,0.2,0.3};
    EXPECT_EQ(goldenVector,vec1*number);
}

TEST(GivenVectorAndNumber, whenAddingNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    double number{3.2};

    phys::Vector goldenVector{4.2,5.2,6.2};
    EXPECT_EQ(goldenVector,vec1+number);
}

TEST(GivenVectorAndNumber, whenSubtractingNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    double number{0.1};

    phys::Vector goldenVector{0.9,1.9,2.9};
    EXPECT_EQ(goldenVector,vec1-number);
}



//class PhysicsNoGravity : public Physics, public ::testing:Test
//{

//};
double updatePosition(current_position, velocity)
{

}
double advanceAcceleration(double acc,double mass,double drag)
{

    double acc_new = acc+(drag/mass);
    return acc_new;
}

TEST(given,d)
{
    double acc{1.5};
    double mass{5.0};
    double drag{.05};
    double acc_new = advanceAcceleration(acc,mass,drag);
    EXPECT_EQ(0,0);
}
