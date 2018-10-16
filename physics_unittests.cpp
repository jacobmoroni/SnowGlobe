#include <gtest/gtest.h>
#include "vector.h"
#include "physics.h"

bool expectNear(phys::Vector vec1, phys::Vector vec2, double threshold)
{
    vec1 = vec1.abs();
    vec2 = vec2.abs();
    double abs_x{(vec1.getX()-vec2.getX())};
    double abs_y{(vec1.getY()-vec2.getY())};
    double abs_z{(vec1.getZ()-vec2.getZ())};
    if (abs_x<=threshold && abs_x>=-threshold && abs_y<=threshold && abs_y >= -threshold && abs_z<=threshold && abs_z>=-threshold)
        return true;
    else
        return false;
}

TEST(Given0InitialState, whenTimeStepOccurs_StateIsCorrect)
{
    phys::Vector velocity{0,0,0};
    phys::Vector accel{0,0,0};
    phys::Vector position{0,0,0};
    double radius{1.0};
    double mass{1.0};
    double coeff_restitution{0.8};
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
    double radius{1.5};
    double mass{1.5};
    double coeff_restitution{0.8};
    double coeff_drag{0.2};
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
    double radius{0.1};
    double mass{1.0};
    double coeff_restitution{0.8};
    double coeff_drag{0.2};
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

    double radius{0.5};

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

    double radius{0.5};
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
    double radius{0.5};


    phys::Vector box_top_right{5,5,5};
    phys::Vector box_bottom_left{-5,-5,-5};
    phys::Physics physics;
    EXPECT_EQ(none,physics.checkForCollission(positionx, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(none,physics.checkForCollission(positiony, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(none,physics.checkForCollission(positionz, box_top_right, box_bottom_left, radius));
}

TEST(givenCollidingPosition, whenXCollisionIsFound_XVelocityReverses)
{
    double radius{1};
    phys::Vector position{4,0,0};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    double mass{1.0};
    double coeff_restitution{0.8};
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
    double radius{1};
    phys::Vector position{0,-5,0};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    double mass{1.0};
    double coeff_restitution{0.8};
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
    double radius{1};
    phys::Vector position{0,0,5};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    double mass{1.0};
    double coeff_restitution{0.8};
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
    double radius{3};
    phys::Vector position{0,0,5};
    phys::Vector velocity{7,7,7};
    phys::Vector accel{0,0,-9.8};
    double mass{1.0};
    double coeff_restitution{0.8};
    Sphere *sphere = new Sphere(position,velocity,accel,radius,mass,coeff_restitution);
    double golden_area(0.5*3.14159*3*3);

    EXPECT_NEAR(golden_area, sphere->getArea(),0.001);
    delete sphere;
}
