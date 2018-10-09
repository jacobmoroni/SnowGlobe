#include "vector.h"

namespace phys {

    Vector::Vector(){}

    Vector::Vector(float x,float y, float z):
        m_x{x}, m_y{y}, m_z{z}
    {
    }

    float Vector::getX() const
    {
        return this->m_x;
    }

    float Vector::getY() const
    {
        return this->m_y;
    }

    float Vector::getZ() const
    {
        return this->m_z;
    }

    Vector Vector::operator +(Vector rhs)
    {
        return Vector{this->m_x + rhs.m_x, this->m_y + rhs.m_y, this->m_z + rhs.m_z};
    }

    Vector Vector::operator -(Vector rhs)
    {
        return Vector{this->m_x - rhs.m_x, this->m_y - rhs.m_y, this->m_z - rhs.m_z};
    }

    Vector Vector::operator *(float number)
    {
        return Vector{this->m_x*number, this->m_y*number, this->m_z*number};
    }

    Vector Vector::operator +(float number)
    {
        return Vector{this->m_x+number, this->m_y+number, this->m_z+number};
    }

    Vector Vector::operator -(float number)
    {
        return Vector{this->m_x-number, this->m_y-number, this->m_z-number};
    }

    Vector Vector::operator -()
    {
        return Vector{-this->m_x,-this->m_y, -this->m_z};
    }

    bool Vector::operator ==(const Vector rhs) const
    {
        if (this->m_x == rhs.m_x && this->m_y == rhs.m_y && this->m_z==rhs.m_z)
            return true;
        else
            return false;
    }

    Vector Vector::operator =(Vector rhs)
    {
        return{this->m_x=rhs.m_x,this->m_y=rhs.m_y,this->m_z=rhs.m_z};
    }
}
