#include <gtest/gtest.h>
#include "vector.h"
#include "physics.h"

bool expectNear(phys::Vector vec1, phys::Vector vec2, float threshold)
{
    vec1 = vec1.abs();
    vec2 = vec2.abs();
    float abs_x{(vec1.getX()-vec2.getX())};
    float abs_y{(vec1.getY()-vec2.getY())};
    float abs_z{(vec1.getZ()-vec2.getZ())};
    if (abs_x<=threshold && abs_x>=-threshold && abs_y<=threshold && abs_y >= -threshold && abs_z<=threshold && abs_z>=-threshold)
        return true;
    else
        return false;
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
    float golden_norm_1{1};
    float golden_norm_2{1.73205};
    float golden_norm_3{3.74166};

    EXPECT_EQ(golden_norm_1,vec1.norm());
    EXPECT_NEAR(golden_norm_2,vec2.norm(),0.0001);
    EXPECT_NEAR(golden_norm_3,vec3.norm(),0.0001);
}

TEST(GivenSingleVector, whenAdjustingNorm_NewNormIsCorrect)
{
    float vec_scalar{10};
    float vec_x{1};
    float vec_y{.5};
    float vec_z{-1.3};
    phys::Vector vec{vec_x,vec_y,vec_z};
    phys::Vector new_vec = (vec/vec.norm())*vec_scalar;
    float golden_norm{1.71464};
    float golden_new_norm{10};
    EXPECT_NEAR(golden_norm, vec.norm(),0.00001);
    EXPECT_NEAR(golden_new_norm,new_vec.norm(),0.000001);
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

TEST(Given2Vectors, whenMultiplying2Vectors_OutputIsCorrect_Test)
{
    phys::Vector vec1{1.0,2.0,3.0};
    phys::Vector vec2{2.0,-3.0,4.0};
    phys::Vector golden_vector{2.0,-6.0,12.0};

    EXPECT_EQ(golden_vector,(vec1*vec2));
}
TEST(GivenVectorAndNumber, whenMultiplyingByNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    float number{0.1};

    phys::Vector golden_vector{0.1,0.2,0.3};
    EXPECT_EQ(golden_vector,vec1*number);
}

TEST(GivenVectorAndNumber, whenDivdingByNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    float number{2.0};

    phys::Vector golden_vector{0.5,1.0,1.5};
    EXPECT_EQ(golden_vector,vec1/number);
}

TEST(GivenVectorAndNumber, whenAddingNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    float number{3.2};

    phys::Vector golden_vector{4.2,5.2,6.2};
    EXPECT_EQ(golden_vector,vec1+number);
}

TEST(GivenVectorAndNumber, whenSubtractingNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    float number{0.1};

    phys::Vector golden_vector{0.9,1.9,2.9};
    EXPECT_EQ(golden_vector,vec1-number);
}

TEST(Given0InitialState, whenTimeStepOccurs_StateIsCorrect)
{
    phys::Vector velocity{0,0,0};
    phys::Vector accel{0,0,0};
    phys::Vector position{0,0,0};
    float radius{1.0};
    float mass{1.0};
    float coeff_restitution{0.8};
    Sphere *sphere = new Sphere(position,velocity,accel,radius,mass,coeff_restitution);

    phys::Vector golden_velocity_1_time_step{0.0,0.0,0.0};
    phys::Vector golden_position_1_time_step{0.0,0.0,0.0};
    phys::Physics physics;
    physics.setGravity(phys::Vector{0,0,0});
    physics.updatePosition(sphere);

    EXPECT_TRUE(expectNear(velocity, golden_velocity_1_time_step, 0.001));
    EXPECT_TRUE(expectNear(sphere->getVelocity(), golden_position_1_time_step, 0.001));
    delete sphere;
}

TEST(GivenInitialState, whenTimeStepOccurs_StateIsCorrect)
{
    phys::Vector velocity{7.0,0,0};
    phys::Vector accel{0,0,-9.8};
    phys::Vector position{0,0,0};
    float radius{1.5};
    float mass{1.5};
    float coeff_restitution{0.8};
    float coeff_drag{0.2};
    Sphere *sphere = new Sphere(position,velocity,accel,radius,mass,coeff_restitution);
    sphere->setCoeffDrag(coeff_drag);
    phys::Vector golden_velocity_1_time_step{6.50932,0.0,-0.326667};
    phys::Vector golden_position_1_time_step{0.216977,0.0,-0.0108889};
    phys::Physics physics;
    physics.updatePosition(sphere);
    physics.setGravity(phys::Vector{0,0,-9.8});

    EXPECT_TRUE(expectNear(sphere->getVelocity(), golden_velocity_1_time_step, 0.00001));
    EXPECT_TRUE(expectNear(sphere->getPosition(), golden_position_1_time_step, 0.00001));
    delete sphere;
}

TEST(givenInitaialState, after2TimeSteps_StateIsCorrect)
{
    phys::Vector velocity{7.0,0,0};
    phys::Vector accel{0,0,-9.8};
    phys::Vector position{0,0,0};
    float radius{0.1};
    float mass{1.0};
    float coeff_restitution{0.8};
    float coeff_drag{0.2};
    Sphere *sphere = new Sphere(position,velocity,accel,radius,mass,coeff_restitution);
    sphere->setCoeffDrag(coeff_drag);
    phys::Vector golden_velocity_1_time_step{6.993461,0.0,-0.653326};
    phys::Vector golden_position_1_time_step{0.466339,0.0,-0.032666};
    phys::Physics physics;
    physics.setGravity(phys::Vector{0,0,-9.8});
    physics.updatePosition(sphere);
    physics.updatePosition(sphere);

    EXPECT_TRUE(expectNear(sphere->getVelocity(),golden_velocity_1_time_step, 0.00001));
    EXPECT_TRUE(expectNear(sphere->getPosition(), golden_position_1_time_step, 0.00001));
    delete sphere;
}

TEST(givenSingleCollidingPosition, whenCollisionIsChecked_ReturnsCollision)
{
    const unsigned char x_wall_pos = 1 << 0;
    const unsigned char x_wall_neg = 1 << 1;
    const unsigned char y_wall_pos = 1 << 2;
    const unsigned char y_wall_neg = 1 << 3;
    const unsigned char z_wall_pos = 1 << 4;
    const unsigned char z_wall_neg = 1 << 5;

    phys::Vector position_x_neg{-5,0,0};
    phys::Vector position_x_pos{5,0,0};
    phys::Vector position_y_neg{0,-5,0};
    phys::Vector position_y_pos{0,5,0};
    phys::Vector position_z_neg{0,0,-5};
    phys::Vector position_z_pos{0,0,5};

    float radius{0.5};

    phys::Vector box_top_right{5,5,5};
    phys::Vector box_bottom_left{-5,-5,-5};
    phys::Physics physics;
    EXPECT_EQ(x_wall_neg,physics.checkForCollission(position_x_neg, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(x_wall_pos,physics.checkForCollission(position_x_pos, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(y_wall_neg,physics.checkForCollission(position_y_neg, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(y_wall_pos,physics.checkForCollission(position_y_pos, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(z_wall_neg,physics.checkForCollission(position_z_neg, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(z_wall_pos,physics.checkForCollission(position_z_pos, box_top_right, box_bottom_left, radius));
}

TEST(givenMultipleCollidingPosition, whenCollisionIsChecked_ReturnsCollision)
{
    const unsigned char x_wall_pos = 1 << 0;
    const unsigned char x_wall_neg = 1 << 1;
    const unsigned char y_wall_pos = 1 << 2;
    const unsigned char y_wall_neg = 1 << 3;
    const unsigned char z_wall_pos = 1 << 4;
    const unsigned char z_wall_neg = 1 << 5;
    const unsigned char none = 0;

    phys::Vector position_x_neg_y_pos{-5,5,0};
    phys::Vector position_x_pos_z_pos{5,0,5};
    phys::Vector position_x_pos_yz_neg{5,-5,-5};

    float radius{0.5};
    phys::Vector box_top_right{5,5,5};
    phys::Vector box_bottom_left{-5,-5,-5};
    phys::Physics physics;

    EXPECT_EQ((x_wall_neg | y_wall_pos),physics.checkForCollission(position_x_neg_y_pos, box_top_right, box_bottom_left, radius));
    EXPECT_EQ((x_wall_pos | z_wall_pos),physics.checkForCollission(position_x_pos_z_pos, box_top_right, box_bottom_left, radius));
    EXPECT_EQ((x_wall_pos | y_wall_neg | z_wall_neg),physics.checkForCollission(position_x_pos_yz_neg, box_top_right, box_bottom_left, radius));
}

TEST(givenNonCollidingPosition, whenCollisionIsChecked_ReturnsNoCollision)
{
    int none{0};
    phys::Vector positionx{-3,1,0};
    phys::Vector positiony{2,4,0};
    phys::Vector positionz{1,1,1};
    float radius{0.5};


    phys::Vector box_top_right{5,5,5};
    phys::Vector box_bottom_left{-5,-5,-5};
    phys::Physics physics;
    EXPECT_EQ(none,physics.checkForCollission(positionx, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(none,physics.checkForCollission(positiony, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(none,physics.checkForCollission(positionz, box_top_right, box_bottom_left, radius));
}

TEST(givenCollidingPosition, whenXCollisionIsFound_XVelocityReverses)
{
    float radius{1};
    phys::Vector position{4,0,0};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    float mass{1.0};
    float coeff_restitution{0.8};
    Sphere *sphere = new Sphere(position,velocity,accel,radius,mass,coeff_restitution);
    phys::Vector box_top_right{5,5,5};
    phys::Vector box_bottom_left{-5,-5,-5};
    phys::Physics physics;
    physics.bounceOffWallWhenCollisionDetected(sphere,box_top_right,box_bottom_left);
    phys::Vector golden_velocity{-5.6,5.6,5.6};

    EXPECT_TRUE(expectNear(golden_velocity,sphere->getVelocity(),0.001));
    delete sphere;
}

TEST(givenCollidingPosition, whenYCollisionIsFound_YVelocityReverses)
{
    float radius{1};
    phys::Vector position{0,-5,0};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    float mass{1.0};
    float coeff_restitution{0.8};
    Sphere *sphere = new Sphere(position,velocity,accel,radius,mass,coeff_restitution);

    phys::Vector box_top_right{5,5,5};
    phys::Vector box_bottom_left{-5,-5,-5};
    phys::Physics physics;
    physics.bounceOffWallWhenCollisionDetected(sphere,box_top_right,box_bottom_left);
    phys::Vector golden_velocity{5.6,-5.6,5.6};

    EXPECT_TRUE(expectNear(golden_velocity,sphere->getVelocity(),0.001));
    delete sphere;
}

TEST(givenCollidingPosition, whenZCollisionIsFound_ZVelocityReverses)
{
    float radius{1};
    phys::Vector position{0,0,5};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    float mass{1.0};
    float coeff_restitution{0.8};
    Sphere *sphere = new Sphere(position,velocity,accel,radius,mass,coeff_restitution);

    phys::Vector box_top_right{5,5,5};
    phys::Vector box_bottom_left{-5,-5,-5};
    phys::Physics physics;
    physics.bounceOffWallWhenCollisionDetected(sphere,box_top_right,box_bottom_left);
    phys::Vector golden_velocity{5.6,5.6,-5.6};

    EXPECT_TRUE(expectNear(golden_velocity,sphere->getVelocity(),0.001));
    delete sphere;
}

TEST(givenOneSphere, whenComputingRadius_RadiusIsCorrect)
{
    float radius{3};
    phys::Vector position{0,0,5};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    float mass{1.0};
    float coeff_restitution{0.8};
    Sphere *sphere = new Sphere(position,velocity,accel,radius,mass,coeff_restitution);
    double golden_area(0.5*3.14159*3*3);

    EXPECT_NEAR(golden_area, sphere->getArea(),0.001);
    delete sphere;
}
