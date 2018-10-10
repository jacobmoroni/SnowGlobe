#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"

class Sphere
{
public:
    Sphere();
    Sphere(phys::Vector position, phys::Vector velocity, phys::Vector accel, float radius);

    float getRadius();
    void setRadius(float value);

    phys::Vector getPosition();
    void setPosition(phys::Vector pos);

    phys::Vector getVelocity();
    void setVelocity(phys::Vector vel);

    phys::Vector getAcceleration();
    void setAcceleration(phys::Vector acc);

    phys::Vector getDragForce();

    float getCoeffRestitution();
    void setCoeffRestitution(float value);

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
