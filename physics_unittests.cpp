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
    float number{0.1};

    phys::Vector goldenVector{0.1,0.2,0.3};
    EXPECT_EQ(goldenVector,vec1*number);
}

TEST(GivenVectorAndNumber, whenAddingNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    float number{3.2};

    phys::Vector goldenVector{4.2,5.2,6.2};
    EXPECT_EQ(goldenVector,vec1+number);
}

TEST(GivenVectorAndNumber, whenSubtractingNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    float number{0.1};

    phys::Vector goldenVector{0.9,1.9,2.9};
    EXPECT_EQ(goldenVector,vec1-number);
}



//class PhysicsNoGravity : public Physics, public ::testing:Test
//{

//};


void updateVelocity(phys::Vector &velocity, phys::Vector &accel, float dt)
{
    velocity = velocity+(accel*dt);
}

void updatePosition(phys::Vector &position, phys::Vector &velocity, phys::Vector &accel, float dt)
{
    updateVelocity(velocity, accel, dt);
    position = position + (velocity*dt);
}

float advanceAcceleration(float acc,float mass,float drag)
{

    float acc_new = acc+(drag/mass);
    return acc_new;
}

TEST(GivenInitialState, whenTimeStepOccurs_StateIsCorrect)
{
    phys::Vector velocity{7.0,0,0};
    phys::Vector accel{0,0,-9.8};
    phys::Vector position{0,0,0};
    float dt = 0.1;
    phys::Vector golden_velocity_1_time_step{7.0,0.0,-0.98};
    phys::Vector golden_position_1_time_step{0.7,0.0,-0.098};
    updatePosition(position,velocity,accel,dt);
    EXPECT_EQ(velocity,golden_velocity_1_time_step);
//    EXPECT_NEAR(position,golden_position_1_time_step,0.001);
}
TEST(given,d)
{
    float acc{1.5};
    float mass{5.0};
    float drag{.05};
    float acc_new = advanceAcceleration(acc,mass,drag);
    EXPECT_EQ(0,0);
}
