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

TEST(Given2Vectors,whenSubtracting2Vectors_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    phys::Vector vec2{3.0, 5.0, 1.0};
    phys::Vector golden_vector{-2.0,-3.0,2.0};

    EXPECT_EQ(golden_vector,vec1-vec2);
}

TEST(GivenVectorAndNumber, whenMultiplyingByNumber_OutputIsCorrect)
{
    phys::Vector vec1{1.0, 2.0, 3.0};
    float number{0.1};

    phys::Vector golden_vector{0.1,0.2,0.3};
    EXPECT_EQ(golden_vector,vec1*number);
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
    phys::Vector drag_force{0,0,0};
    float mass = 1.0;
    float dt = 0.1;
    phys::Vector golden_velocity_1_time_step{0.0,0.0,0.0};
    phys::Vector golden_position_1_time_step{0.0,0.0,0.0};
    phys::Physics physics;
    physics.updatePosition(position,velocity,accel,drag_force,mass);

    EXPECT_TRUE(expectNear(velocity, golden_velocity_1_time_step, 0.001));
    EXPECT_TRUE(expectNear(position, golden_position_1_time_step, 0.001));
}

TEST(GivenInitialState, whenTimeStepOccurs_StateIsCorrect)
{
    phys::Vector velocity{7.0,0,0};
    phys::Vector accel{0,0,-9.8};
    phys::Vector position{0,0,0};
    phys::Vector drag_force{0,0,0};
    float mass = 1.0;
    float dt = 0.1;
    phys::Vector golden_velocity_1_time_step{7.0,0.0,-0.326667};
    phys::Vector golden_position_1_time_step{0.23333,0.0,-0.0108889};
    phys::Physics physics;
    physics.updatePosition(position,velocity,accel,drag_force,mass);

    EXPECT_TRUE(expectNear(velocity, golden_velocity_1_time_step, 0.001));
    EXPECT_TRUE(expectNear(position, golden_position_1_time_step, 0.001));
}

TEST(givenInitaialState, after2TimeSteps_StateIsCorrect)
{
    phys::Vector velocity{7.0,0,0};
    phys::Vector accel{0,0,-9.8};
    phys::Vector position{0,0,0};
    phys::Vector drag_force{0,0,0};
    float mass = 1.0;
    float dt = 0.1;
    phys::Vector golden_velocity_1_time_step{7.0,0.0,-.653334};
    phys::Vector golden_position_1_time_step{0.46667,0.0,-0.032667};
    phys::Physics physics;
    physics.updatePosition(position,velocity,accel,drag_force,mass);
    physics.updatePosition(position,velocity,accel,drag_force,mass);

    EXPECT_TRUE(expectNear(velocity,golden_velocity_1_time_step, 0.001));
    EXPECT_TRUE(expectNear(position, golden_position_1_time_step, 0.0001));
}

TEST(givenCollidingPosition, whenCollisionIsChecked_ReturnsCollision)
{
    const int none{0};
    const int x_wall_pos{1};
    const int y_wall_pos{2};
    const int z_wall_pos{3};
    const int x_wall_neg{4};
    const int y_wall_neg{5};
    const int z_wall_neg{6};

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
    float sphere_radius{1};
    phys::Vector position{4,0,0};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    Sphere* sphere = new Sphere(position,
                        velocity,
                        sphere_radius,
                        accel);
    phys::Vector box_top_right{5,5,5};
    phys::Vector box_bottom_left{-5,-5,-5};
    phys::Physics physics;
    physics.bounceOffWallWhenCollisionDetected(sphere,box_top_right,box_bottom_left);
    phys::Vector golden_velocity{-5.6,5.6,5.6};

    EXPECT_TRUE(expectNear(golden_velocity,sphere->getVelocity(),0.001));
}

TEST(givenCollidingPosition, whenYCollisionIsFound_YVelocityReverses)
{
    float sphere_radius{1};
    phys::Vector position{0,-5,0};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    Sphere* sphere = new Sphere(position,
                        velocity,
                        sphere_radius,
                        accel);
    phys::Vector box_top_right{5,5,5};
    phys::Vector box_bottom_left{-5,-5,-5};
    phys::Physics physics;
    physics.bounceOffWallWhenCollisionDetected(sphere,box_top_right,box_bottom_left);
    phys::Vector golden_velocity{5.6,-5.6,5.6};

    EXPECT_TRUE(expectNear(golden_velocity,sphere->getVelocity(),0.001));
}

TEST(givenCollidingPosition, whenZCollisionIsFound_ZVelocityReverses)
{
    float sphere_radius{1};
    phys::Vector position{0,0,5};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    Sphere* sphere = new Sphere(position,
                        velocity,
                        sphere_radius,
                        accel);
    phys::Vector box_top_right{5,5,5};
    phys::Vector box_bottom_left{-5,-5,-5};
    phys::Physics physics;
    physics.bounceOffWallWhenCollisionDetected(sphere,box_top_right,box_bottom_left);
    phys::Vector golden_velocity{5.6,5.6,-5.6};

    EXPECT_TRUE(expectNear(golden_velocity,sphere->getVelocity(),0.001));
}
