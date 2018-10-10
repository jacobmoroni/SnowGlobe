#include "sphere.h"
#include "vector.h"

Sphere::Sphere(){}
Sphere::Sphere(phys::Vector postion,
               phys::Vector velocity,
               phys::Vector accel,
               float radius) :
    m_position{postion}, m_velocity{velocity}, m_accel{accel}, m_radius{radius}
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

phys::Vector Sphere::getPosition()
{
    return m_position;
}

void Sphere::setPosition(phys::Vector pos)
{
    m_position.setVector(pos);
}

phys::Vector Sphere::getVelocity()
{
    return m_velocity;
}

void Sphere::setVelocity(phys::Vector vel)
{
    m_velocity.setVector(vel);
}

phys::Vector Sphere::getAcceleration()
{
    return m_accel;
}

void Sphere::setAcceleration(phys::Vector acc)
{
    m_accel.setVector(acc);
}

phys::Vector Sphere::getDragForce()
{
    return m_drag_force;
}

float Sphere::getCoeffRestitution()
{
    return m_coeff_restitution;
}

void Sphere::setCoeffRestitution(float value)
{
    m_coeff_restitution = value;
}

float Sphere::getMass()
{
    return m_mass;
}
