#include "sphere.h"
#include "vector.h"

Sphere::Sphere(){}
Sphere::Sphere(phys::Vector postion,
               phys::Vector velocity,
               float radius,
               phys::Vector accel) :
    m_position{postion}, m_velocity{velocity}, m_radius{radius}, m_accel{accel}
{
}

float Sphere::getRadius()
{
    return m_radius;
}

void Sphere::setRadius(float value)
{
    m_radius = value;
}

phys::Vector& Sphere::getPosition()
{
    return m_position;
}

void Sphere::setPosition(float x, float y, float z)
{
    m_position.setVector(x, y, z);
}

phys::Vector& Sphere::getVelocity()
{
    return m_velocity;
}

void Sphere::setVelocity(float x, float y, float z)
{
    m_velocity.setVector(x, y, z);
}

float Sphere::getCoeffRestitution()
{
    return m_coeff_restitution;
}

void Sphere::setCoeffRestitution(float value)
{
    m_coeff_restitution = value;
}

phys::Vector& Sphere::getAcceleration()
{
    return m_accel;
}

phys::Vector Sphere::getDragForce()
{
    return m_drag_force;
}

float Sphere::getMass()
{
    return m_mass;
}
