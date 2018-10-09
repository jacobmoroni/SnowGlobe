#include <gtest/gtest.h>
#include "vector.h"

//class PhysicsNoGravity : public Physics, public ::testing:Test
//{

//};

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

TEST(addingVectors,whenAdding2Vectors_OutputIsCorrect)
{
    phys::Vector vec1{1.0,1.0,1.0};
    phys::Vector vec2{2.0,2.0,2.0};

    phys::Vector answer_vec{3.0,3.0,3.0};

    EXPECT_EQ(answer_vec, vec1+vec2);
}
