#include "physics.h"
#include "vector.h"
#include <iostream>
#include <algorithm>
#include "sphere.h"

namespace phys {
Physics::Physics(){}

void Physics::updateAcceleration(Sphere *sphere)
{
    this->updateDragForce(sphere);
    sphere->setAcceleration(Vector{m_gravity+(sphere->getDragForce()/sphere->getMass())});
}

void Physics::updateVelocity(Sphere *sphere)
{
    this->updateAcceleration(sphere);
    sphere->setVelocity(Vector{sphere->getVelocity()+(sphere->getAcceleration()*m_dt)});
}

void Physics::updatePosition(Sphere *sphere)
{
    this->updateVelocity(sphere);
    sphere->setPosition(Vector{sphere->getPosition() + sphere->getVelocity()*m_dt});
}

void Physics::updateDragForce(Sphere *sphere)
{
    Vector force{(sphere->getVelocity()*sphere->getVelocity())*0.5*m_density*sphere->getCoeffDrag()*sphere->getArea()};
    force = sphere->getVelocity().sign()*force*-1;
    sphere->setDragForce(force);
}

void Physics::bounceOffWallWhenCollisionDetected(Sphere *sphere, Vector box_top_right, Vector box_bottom_left)
{
    unsigned char collision_detection{this->checkForBoxCollission(sphere->getPosition(), box_top_right, box_bottom_left, sphere->getRadius())};
    const unsigned char x_wall_pos = 1 << 0;
    const unsigned char x_wall_neg = 1 << 1;
    const unsigned char y_wall_pos = 1 << 2;
    const unsigned char y_wall_neg = 1 << 3;
    const unsigned char z_wall_pos = 1 << 4;
    const unsigned char z_wall_neg = 1 << 5;
    const unsigned char none = 0;
    double overshoot{0.0};
    Vector bounce{1,1,1};

    if (collision_detection & ~none)
    {
        if (collision_detection & x_wall_pos)
        {
            overshoot = box_top_right.getX()-(sphere->getPosition().getX()+sphere->getRadius());
            bounce = bounce*Vector{-1,1,1};
            sphere->setPosition(Vector{sphere->getPosition().getX()+overshoot,sphere->getPosition().getY(),sphere->getPosition().getZ()});
        }
        if (collision_detection & y_wall_pos)
        {
            overshoot = box_top_right.getY()-(sphere->getPosition().getY()+sphere->getRadius());
            bounce = bounce*Vector{1,-1,1};
            sphere->setPosition(Vector{sphere->getPosition().getX(),sphere->getPosition().getY()+overshoot,sphere->getPosition().getZ()});
        }
        if (collision_detection & z_wall_pos)
        {
            overshoot = box_top_right.getZ()-(sphere->getPosition().getZ()+sphere->getRadius());
            bounce = bounce*Vector{1,1,-1};
            sphere->setPosition(Vector{sphere->getPosition().getX(),sphere->getPosition().getY(),sphere->getPosition().getZ()+overshoot});
        }
        if (collision_detection & x_wall_neg)
        {
            overshoot = box_bottom_left.getX()-(sphere->getPosition().getX()-sphere->getRadius());
            bounce = bounce*Vector{-1,1,1};
            sphere->setPosition(Vector{sphere->getPosition().getX()+overshoot,sphere->getPosition().getY(),sphere->getPosition().getZ()});
        }
        if (collision_detection & y_wall_neg)
        {
            overshoot = box_bottom_left.getY()-(sphere->getPosition().getY()-sphere->getRadius());
            bounce = bounce*Vector{1,-1,1};
            sphere->setPosition(Vector{sphere->getPosition().getX(),sphere->getPosition().getY()+overshoot,sphere->getPosition().getZ()});
        }
        if (collision_detection & z_wall_neg)
        {
            overshoot = box_bottom_left.getZ()-(sphere->getPosition().getZ()-sphere->getRadius());
            bounce = bounce*Vector{1,1,-1};
            sphere->setPosition(Vector{sphere->getPosition().getX(),sphere->getPosition().getY(),sphere->getPosition().getZ()+overshoot});
        }
        Vector new_vel{sphere->getVelocity()};
        new_vel = (new_vel*bounce)*sphere->getCoeffRestitution();
        sphere->setVelocity(new_vel);
    }

}

unsigned char Physics::checkForBoxCollission(Vector position, Vector box_top_right, Vector box_bottom_left, double radius)
{
    const unsigned char x_wall_pos = 1 << 0;
    const unsigned char x_wall_neg = 1 << 1;
    const unsigned char y_wall_pos = 1 << 2;
    const unsigned char y_wall_neg = 1 << 3;
    const unsigned char z_wall_pos = 1 << 4;
    const unsigned char z_wall_neg = 1 << 5;

    unsigned char output{0};

    if (position.getX()+radius >= box_top_right.getX())
        output |= x_wall_pos;
    if (position.getX()-radius <= box_bottom_left.getX())
        output |= x_wall_neg;
    if (position.getY()+radius >= box_top_right.getY())
        output |= y_wall_pos;
    if (position.getY()-radius <= box_bottom_left.getY())
        output |= y_wall_neg;
    if (position.getZ()+radius >= box_top_right.getZ())
        output |= z_wall_pos;
    if (position.getZ()-radius <= box_bottom_left.getZ())
        output |= z_wall_neg;

    return output;
}

void Physics::setGravity(Vector gravity)
{
    m_gravity = gravity;
}

Vector Physics::getGravity()
{
    return m_gravity;
}

void Physics::setDensity(double density)
{
    m_density = density;
}

double Physics::getDensity()
{
    return m_density;
}

void Physics::checkForSphereCollision(std::vector<Sphere *> &spheres)
{
    for (int i=0; i<spheres.size(); i++)
    {
        for (int j=i+1; j<spheres.size(); j++)
        {
            Vector pos_d{spheres[i]->getPosition()-spheres[j]->getPosition()};
            if (pos_d.norm()+m_collision_buffer < (spheres[i]->getRadius()+spheres[j]->getRadius()))
            {
                bounceOffSphere(spheres[i],spheres[j]);
                adjustPositionAfterBounce(spheres[i],spheres[j]);
            }
        }
    }
}

void Physics::bounceOffSphere(Sphere *sphere1, Sphere *sphere2)
{
    double mass1_term{2*sphere2->getMass()/(sphere1->getMass()+sphere2->getMass())};
    phys::Vector vel1_diff{sphere1->getVelocity()-sphere2->getVelocity()};
    phys::Vector pos1_diff{sphere1->getPosition()-sphere2->getPosition()};
    double vel1_diff_dotted{vel1_diff.dot(pos1_diff)};
    double pos1_norm_squared{pos1_diff.norm()*pos1_diff.norm()};
    phys::Vector new_vel1{sphere1->getCoeffRestitution()*(sphere1->getVelocity()-mass1_term*vel1_diff_dotted/pos1_norm_squared*pos1_diff)};

    double mass2_term{2*sphere1->getMass()/(sphere1->getMass()+sphere2->getMass())};
    phys::Vector vel2_diff{sphere2->getVelocity()-sphere1->getVelocity()};
    phys::Vector pos2_diff{sphere2->getPosition()-sphere1->getPosition()};
    double vel2_diff_dotted{vel2_diff.dot(pos2_diff)};
    double pos2_norm_squared{pos2_diff.norm()*pos2_diff.norm()};
    phys::Vector new_vel2{sphere2->getCoeffRestitution()*(sphere2->getVelocity()-mass2_term*vel2_diff_dotted/pos2_norm_squared*pos2_diff)};

    sphere1->setVelocity(new_vel1);
    sphere2->setVelocity(new_vel2);
}

void Physics::adjustPositionAfterBounce(Sphere *sphere1, Sphere *sphere2)
{
    Vector pos1_diff{sphere1->getPosition()-sphere2->getPosition()};
    Vector pos2_diff{sphere2->getPosition()-sphere1->getPosition()};
    double overlap = (sphere1->getRadius()+sphere2->getRadius()) - pos1_diff.norm();
    Vector new_pos1{sphere1->getPosition()+(overlap/2)*(pos1_diff/pos1_diff.norm())};
    Vector new_pos2{sphere2->getPosition()+(overlap/2)*(pos2_diff/pos2_diff.norm())};
    sphere1->setPosition(new_pos1);
    sphere2->setPosition(new_pos2);
}
}

double saturateNumber(double value, double min_val, double max_val)
{
    return double(std::max(std::min(max_val, value),min_val));
}
