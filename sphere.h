#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"

class Sphere
{
public:
    Sphere();
    Sphere(phys::Vector position, phys::Vector velocity, phys::Vector accel, double radius, double mass, double coeff_restitution);


    double getRadius();
    void setRadius(double value);

    phys::Vector getPosition();
    void setPosition(phys::Vector pos);

    phys::Vector getVelocity();
    void setVelocity(phys::Vector vel);

    phys::Vector getAcceleration();
    void setAcceleration(phys::Vector acc);

    phys::Vector getDragForce();
    void setDragForce(phys::Vector drag_force);

    double getCoeffRestitution();
    void setCoeffRestitution(double value);

    double getMass();
    double getArea();

    double getCoeffDrag();
    void setCoeffDrag(double value);

private:
    phys::Vector m_position;
    phys::Vector m_velocity;
    phys::Vector m_accel;
    phys::Vector m_drag_force;
    double m_radius{1};
    double m_mass{1};
    double m_coeff_restitution{0.8};
    double m_coeff_drag{0.3};
    double pi{3.14159};
    double m_area = 0.5*pi*m_radius*m_radius;
};

#endif // SPHERE_H
