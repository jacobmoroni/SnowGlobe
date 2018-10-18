#include <gtest/gtest.h>
#include "vector.h"
#include <vector>
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

TEST(GivenNumberAndSaturationValues, whenNumberIsSaturated_SaturatedValuesAreCorrect)
{
    double num1{100};
    double num2{5};
    double num3{30};
    double min_value{10};
    double max_value{90};

    EXPECT_EQ(max_value, saturateNumber(num1,min_value,max_value));
    EXPECT_EQ(min_value, saturateNumber(num2,min_value,max_value));
    EXPECT_EQ(num3, saturateNumber(num3,min_value,max_value));
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
    phys::Vector golden_acceleration_1_time_step{0.0,0.0,0.0};
    phys::Vector golden_drag_force_1_time_step{0.0,0.0,0.0};
    phys::Physics physics;
    physics.setGravity(phys::Vector{0,0,0});
    physics.updatePosition(sphere);

    EXPECT_TRUE(expectNear(sphere->getVelocity(), golden_velocity_1_time_step, 0.00001));
    EXPECT_TRUE(expectNear(sphere->getPosition(), golden_position_1_time_step, 0.00001));
    EXPECT_TRUE(expectNear(sphere->getAcceleration(), golden_acceleration_1_time_step,0.00001));
    EXPECT_TRUE(expectNear(sphere->getDragForce(), golden_drag_force_1_time_step,0.00001));
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
    phys::Vector golden_acceleration_1_time_step{-14.72031,0.0,-9.8000};
    phys::Vector golden_drag_force_1_time_step{-22.08046,0.0,0.0};
    phys::Physics physics;
    physics.updatePosition(sphere);
    physics.setGravity(phys::Vector{0,0,-9.8});

    EXPECT_TRUE(expectNear(sphere->getVelocity(), golden_velocity_1_time_step, 0.00001));
    EXPECT_TRUE(expectNear(sphere->getPosition(), golden_position_1_time_step, 0.00001));
    EXPECT_TRUE(expectNear(sphere->getAcceleration(), golden_acceleration_1_time_step,0.00001));
    EXPECT_TRUE(expectNear(sphere->getDragForce(), golden_drag_force_1_time_step,0.00001));
    delete sphere;
}

TEST(givenInitaialState, after2TimeSteps_StateIsCorrect)
{
    phys::Vector velocity{7.0,0,0};
    phys::Vector accel{1.5,2.5,-9.8};
    phys::Vector position{0,0,0};
    double radius{0.1};
    double mass{1.0};
    double coeff_restitution{0.8};
    double coeff_drag{0.2};
    Sphere *sphere = new Sphere(position,velocity,accel,radius,mass,coeff_restitution);
    sphere->setCoeffDrag(coeff_drag);
    phys::Vector golden_velocity_2_time_step{7.093413819,
                                             0.1666662031,
                                             -0.6533262094};
    phys::Vector golden_position_2_time_step{0.471338088,
                                             0.00833331788,
                                             -0.0326664292};
    phys::Vector golden_acceleration_2_time_step{1.400549994,
                                                 2.499986092,
                                                 -9.799786283};
    phys::Vector golden_drag_force_2_time_step{-0.09945000574,
                                               -0.00001390808073,
                                               0.0002137171317};
    phys::Physics physics;
    physics.setGravity(phys::Vector{1.5,2.5,-9.8});
    physics.updatePosition(sphere);
    physics.updatePosition(sphere);

    EXPECT_TRUE(expectNear(sphere->getVelocity(),golden_velocity_2_time_step, 0.00001));
    EXPECT_TRUE(expectNear(sphere->getPosition(), golden_position_2_time_step, 0.00001));
    EXPECT_TRUE(expectNear(sphere->getAcceleration(), golden_acceleration_2_time_step,0.00001));
    EXPECT_TRUE(expectNear(sphere->getDragForce(), golden_drag_force_2_time_step,0.00001));
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
    EXPECT_EQ(x_wall_neg,physics.checkForBoxCollission(position_x_neg, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(x_wall_pos,physics.checkForBoxCollission(position_x_pos, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(y_wall_neg,physics.checkForBoxCollission(position_y_neg, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(y_wall_pos,physics.checkForBoxCollission(position_y_pos, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(z_wall_neg,physics.checkForBoxCollission(position_z_neg, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(z_wall_pos,physics.checkForBoxCollission(position_z_pos, box_top_right, box_bottom_left, radius));
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

    EXPECT_EQ((x_wall_neg | y_wall_pos),physics.checkForBoxCollission(position_x_neg_y_pos, box_top_right, box_bottom_left, radius));
    EXPECT_EQ((x_wall_pos | z_wall_pos),physics.checkForBoxCollission(position_x_pos_z_pos, box_top_right, box_bottom_left, radius));
    EXPECT_EQ((x_wall_pos | y_wall_neg | z_wall_neg),physics.checkForBoxCollission(position_x_pos_yz_neg, box_top_right, box_bottom_left, radius));
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
    EXPECT_EQ(none,physics.checkForBoxCollission(positionx, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(none,physics.checkForBoxCollission(positiony, box_top_right, box_bottom_left, radius));
    EXPECT_EQ(none,physics.checkForBoxCollission(positionz, box_top_right, box_bottom_left, radius));
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

TEST(givenOneSphere, whenComputingArea_AreaIsCorrect)
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

class VectorOfSpheres : public phys::Physics, public ::testing::Test
{
public:
    VectorOfSpheres(){}

    double radius{1};
    double mass{1.0};
    double coeff_restitution{0.8};

    phys::Vector position1{0,0,5};
    phys::Vector velocity1{7,7,7};
    phys::Vector accel1{0,0,-9.8};
    Sphere *sphere1 = new Sphere(position1,velocity1,accel1,radius,mass,coeff_restitution);

    phys::Vector position2{0,0,3.5};
    phys::Vector velocity2{-7,-7,-7};
    phys::Vector accel2{0,0,-9.8};
    Sphere *sphere2 = new Sphere(position2,velocity2,accel2,radius,mass,coeff_restitution);

    phys::Vector position3{0,7,3.5};
    phys::Vector velocity3{7,7,7};
    phys::Vector accel3{0,0,-9.8};
    Sphere *sphere3 = new Sphere(position3,velocity3,accel3,radius,mass,coeff_restitution);

    double mass4{4.0};
    double coeff_restitution4{0.9};
    phys::Vector position4{5,5,5};
    phys::Vector velocity4{-2.1, 3.7, -1.2};
    phys::Vector accel4{0,0,-9.8};
    Sphere *sphere4 = new Sphere(position4,velocity4,accel4,radius,mass4,coeff_restitution4);

    double mass5{2.0};
    double coeff_restitution5{0.2};
    phys::Vector position5{4,6,4};
    phys::Vector velocity5{5, 0, -3.7};
    phys::Vector accel5{0,0,-9.8};
    Sphere *sphere5 = new Sphere(position5,velocity5,accel5,radius,mass5,coeff_restitution5);

    std::vector<Sphere*> spheres{sphere1, sphere2, sphere3, sphere4, sphere5};
};

TEST_F(VectorOfSpheres, whenCheckingVelocityOfSpheresAfterSimpleImpact_VelocityIsCorrect)
{
    phys::Vector golden_velocity1_after_collision{5.6, 5.6, -5.6};
    phys::Vector golden_velocity2_after_collision{-5.6, -5.6, 5.6};
    bounceOffSphere(sphere1, sphere2);
    EXPECT_TRUE(expectNear(golden_velocity1_after_collision,sphere1->getVelocity(),0.0001));
    EXPECT_TRUE(expectNear(golden_velocity2_after_collision,sphere2->getVelocity(),0.0001));
}

TEST_F(VectorOfSpheres, whenCheckingVelocityOfSpheresAfterComplexImpact_VelocityIsCorrect)
{
    phys::Vector golden_velocity4_after_collision{-0.23, 1.67, 0.58};
    phys::Vector golden_velocity5_after_collision{0.2622222222, 0.7377777778, -1.477777778};
    bounceOffSphere(sphere4, sphere5);
    EXPECT_TRUE(expectNear(golden_velocity4_after_collision,sphere4->getVelocity(),0.0001));
    EXPECT_TRUE(expectNear(golden_velocity5_after_collision,sphere5->getVelocity(),0.0001));
}

TEST_F(VectorOfSpheres,whenCollisionIsChecked_CollisionIsDetectedForCollidingSpheres)
{
    phys::Vector golden_vel1{5.6, 5.6, -5.6};
    phys::Vector golden_vel2{-5.6, -5.6, 5.6};
    phys::Vector golden_vel3{7,7,7};
    phys::Vector golden_vel4{-0.23, 1.67, 0.58};
    phys::Vector golden_vel5{0.2622222222, 0.7377777778, -1.477777778};
    checkForSphereCollision(spheres);

    EXPECT_TRUE(expectNear(golden_vel1,sphere1->getVelocity(),0.0001));
    EXPECT_TRUE(expectNear(golden_vel2,sphere2->getVelocity(),0.0001));
    EXPECT_TRUE(expectNear(golden_vel3,sphere3->getVelocity(),0.0001));
    EXPECT_TRUE(expectNear(golden_vel4,sphere4->getVelocity(),0.0001));
    EXPECT_TRUE(expectNear(golden_vel5,sphere5->getVelocity(),0.0001));
}

TEST_F(VectorOfSpheres,whenUpdatingPositionFromBounce_PositionIsCorrect)
{
    phys::Vector golden_pos1{0,0,5.25};
    phys::Vector golden_pos2{0,0,3.25};
    phys::Vector golden_pos4{5.077350269, 4.922649731, 5.077350269};
    phys::Vector golden_pos5{3.922649731, 6.077350269, 3.922649731};
    adjustPositionAfterBounce(sphere1,sphere2);
    adjustPositionAfterBounce(sphere4,sphere5);

    EXPECT_TRUE(expectNear(golden_pos1,sphere1->getPosition(),0.0001));
    EXPECT_TRUE(expectNear(golden_pos2,sphere2->getPosition(),0.0001));
    EXPECT_TRUE(expectNear(golden_pos4,sphere4->getPosition(),0.0001));
    EXPECT_TRUE(expectNear(golden_pos5,sphere5->getPosition(),0.0001));
}
