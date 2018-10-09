#include "vector.h"

namespace phys {

    Vector::Vector(){}

    Vector::Vector(double x,double y, double z):
        m_x{x}, m_y{y}, m_z{z}
    {
    }

    double Vector::getX() const
    {
        return this->m_x;
    }

    double Vector::getY() const
    {
        return this->m_y;
    }

    double Vector::getZ() const
    {
        return this->m_z;
    }

    Vector Vector::operator +(Vector rhs)
    {
        return Vector{this->m_x + rhs.m_x, this->m_y + rhs.m_y, this->m_z + rhs.m_z};
    }

    bool Vector::operator ==(Vector rhs)
    {
        if (this->m_x == rhs.m_x && this->m_y == rhs.m_y && this->m_z==rhs.m_z)
            return true;
        else
            return false;
    }
}
