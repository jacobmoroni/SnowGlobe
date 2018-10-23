#include <gtest/gtest.h>
#include "vector.h"

TEST(GivenNumberAndSaturationValues, whenNumberIsSaturated_SaturatedValuesAreCorrect)
{
    double num1{100};
    double num2{5};
    double num3{30};
    double min_value{10};
    double max_value{90};

    EXPECT_EQ(max_value, phys::saturateNumber(num1,min_value,max_value));
    EXPECT_EQ(min_value, phys::saturateNumber(num2,min_value,max_value));
    EXPECT_EQ(num3, phys::saturateNumber(num3,min_value,max_value));
}

TEST(GivenVectorAndSaturationValues, whenVectorIsSaturated_SaturatedValuesAreCorrect)
{
    phys::Vector vec1{100.0,50.0,0.0};
    double min_value{20.0};
    double max_value{80.0};
    phys::Vector golden_values{max_value,50,min_value};

    EXPECT_EQ(golden_values,vec1.saturate(min_value,max_value));
}

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
    phys::Vector golden_vector{-1.0,-2.0,-3.0};
    EXPECT_EQ(golden_vector,-vec1);
}

TEST(GivenSingleVector, whenAskingForSign_SignIsCorrect)
{
    phys::Vector vec1{-1,2,-3};
    phys::Vector vec2{1,-2,0};
    phys::Vector golden_vec1{-1,1,-1};
    phys::Vector golden_vec2{1,-1,0};

    EXPECT_EQ(golden_vec1,vec1.sign());
    EXPECT_EQ(golden_vec2,vec2.sign());
}

TEST(GivenSingleVector,whenComputingL2Norm_NormIsCorrect)
{
    phys::Vector vec1{1,0,0};
    phys::Vector vec2{1,1,1};
    phys::Vector vec3{2,-1,3};
    double golden_norm_1{1};
    double golden_norm_2{1.73205};
    double golden_norm_3{3.74166};

    EXPECT_EQ(golden_norm_1,vec1.norm());
    EXPECT_NEAR(golden_norm_2,vec2.norm(),0.0001);
    EXPECT_NEAR(golden_norm_3,vec3.norm(),0.0001);
}

TEST(GivenSingleVector, whenAdjustingNorm_NewNormIsCorrect)
{
    double vec_scalar{10};
    double vec_x{1};
    double vec_y{.5};
    double vec_z{-1.3};
    phys::Vector vec{vec_x,vec_y,vec_z};
    phys::Vector new_vec = (vec/vec.norm())*vec_scalar;
    double golden_norm{1.71464};
    double golden_new_norm{10};
    EXPECT_NEAR(golden_norm, vec.norm(),0.00001);
    EXPECT_NEAR(golden_new_norm,new_vec.norm(),0.000001);
}

TEST(GivenSingleVector, whenComputingAbs_AbsoluteValueIsCorrect)
{
    phys::Vector vec{-1,3,-2};
    phys::Vector golden_vec{1,3,2};

    EXPECT_EQ(golden_vec,vec.abs());
}

TEST(Given2Vectors,whenAdding2Vectors_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    phys::Vector vec2{1.0, 2.0, 3.0};
    phys::Vector answer_vector{vec1+vec2};
    phys::Vector golden_vector{2.0,4.0,6.0};

    EXPECT_EQ(2.0,answer_vector.getX());
    EXPECT_EQ(4.0,answer_vector.getY());
    EXPECT_EQ(6.0,answer_vector.getZ());
    EXPECT_EQ(golden_vector,vec1+vec2);
}

TEST(Given2Vectors, whenSubtracting2Vectors_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    phys::Vector vec2{3.0, 5.0, 1.0};
    phys::Vector golden_vector{-2.0,-3.0,2.0};

    EXPECT_EQ(golden_vector,vec1-vec2);
}

TEST(Given2Vectors, whenMultiplying2Vectors_OutputIsCorrect)
{
    phys::Vector vec1{1.0,2.0,3.0};
    phys::Vector vec2{2.0,-3.0,4.0};
    phys::Vector golden_vector{2.0,-6.0,12.0};

    EXPECT_EQ(golden_vector,(vec1*vec2));
}

TEST(Given2Vectors, whenComputingDotProduct_OutputIsCorrect)
{
    phys::Vector vec1{1.0,2.0,3.0};
    phys::Vector vec2{2.0,-3.0,4.0};
    double golden_value{8.0};

    EXPECT_EQ(golden_value,(vec1.dot(vec2)));
}

TEST(GivenVectorAndNumber, whenMultiplyingByNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    double number{2.0};

    phys::Vector golden_vector{2.0,4.0,6.0};
    EXPECT_EQ(golden_vector,vec1*number);
}

TEST(GivenVectorAndNumber, whenDivdingByNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    double number{2.0};

    phys::Vector golden_vector{0.5,1.0,1.5};
    EXPECT_EQ(golden_vector,vec1/number);
}

TEST(GivenVectorAndNumber, whenAddingNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    double number{3.2};

    phys::Vector golden_vector{4.2,5.2,6.2};
    EXPECT_EQ(golden_vector,vec1+number);
}

TEST(GivenVectorAndNumber, whenSubtractingNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    double number{0.1};

    phys::Vector golden_vector{0.9,1.9,2.9};
    EXPECT_EQ(golden_vector,vec1-number);
}
