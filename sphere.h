#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"

class Sphere
{
public:
    Sphere();
    Sphere(phys::Vector position, phys::Vector velocity, float radius, phys::Vector accel);
    float getRadius();
    void setRadius(float value);
    phys::Vector &getPosition();
    void setPosition(float x, float y, float z);
    phys::Vector &getVelocity();
    void setVelocity(float x, float y,float z);
    float getCoeffRestitution();
    void setCoeffRestitution(float value);
    phys::Vector &getAcceleration();
    phys::Vector getDragForce();
    float getMass();

private:
    float m_radius{1};
    phys::Vector m_position;
    phys::Vector m_velocity;
    phys::Vector m_accel;
    phys::Vector m_drag_force;
    float m_mass{1};
    float m_coeff_restitution{0.8};
};

#endif // SPHERE_H
