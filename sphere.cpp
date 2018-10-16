#include "sphere.h"
#include "vector.h"

Sphere::Sphere(){}
Sphere::Sphere(phys::Vector postion,
               phys::Vector velocity,
               phys::Vector accel,
               double radius,
               double mass,
               double coeff_restitution) :
    m_position{postion},
    m_velocity{velocity},
    m_accel{accel},
    m_radius{radius},
    m_mass{mass},
    m_coeff_restitution{coeff_restitution}
{
}

double Sphere::getRadius()
{
    return m_radius;
}

void Sphere::setRadius(double value)
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

void Sphere::setDragForce(phys::Vector drag_force)
{
    m_drag_force.setVector(drag_force);
}

double Sphere::getCoeffRestitution()
{
    return m_coeff_restitution;
}

void Sphere::setCoeffRestitution(double value)
{
    m_coeff_restitution = value;
}

double Sphere::getCoeffDrag()
{
    return m_coeff_drag;
}

void Sphere::setCoeffDrag(double value)
{
    m_coeff_drag = value;
}

double Sphere::getMass()
{
    return m_mass;
}

double Sphere::getArea()
{
    return m_area;
}
