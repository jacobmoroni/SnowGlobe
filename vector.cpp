#include "vector.h"
#include <math.h>
#include <algorithm>

namespace phys {

Vector::Vector(){}

Vector::Vector(double x,double y, double z):
    m_x{x}, m_y{y}, m_z{z}
{
}

double Vector::getX() const
{
    return m_x;
}

double Vector::getY() const
{
    return m_y;
}

double Vector::getZ() const
{
    return m_z;
}

Vector Vector::sign()
{
    double x{(this->getX() > 0.f) ? 1.f : ((this->getX() < 0.f) ? -1.f : 0.f)};
    double y{(this->getY() > 0.f) ? 1.f : ((this->getY() < 0.f) ? -1.f : 0.f)};
    double z{(this->getZ() > 0.f) ? 1.f : ((this->getZ() < 0.f) ? -1.f : 0.f)};

    return Vector{x,y,z};
}

Vector Vector::operator +(Vector rhs)
{
    return Vector{m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z};
}

Vector Vector::operator -(Vector rhs)
{
    return Vector{m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z};
}

Vector Vector::operator *(Vector rhs)
{
    return Vector{m_x*rhs.getX(), m_y*rhs.getY(), m_z*rhs.getZ()};
}
Vector Vector::operator /(double number)
{
    return Vector{m_x/number,m_y/number,m_z/number};
}

Vector Vector::operator *(double number)
{
    return Vector{m_x*number, m_y*number, m_z*number};
}

Vector Vector::operator +(double number)
{
    return Vector{m_x+number, m_y+number, m_z+number};
}

Vector Vector::operator -(double number)
{
    return Vector{m_x-number, m_y-number, m_z-number};
}

Vector Vector::operator -()
{
    return Vector{-m_x,-m_y, -m_z};
}

bool Vector::operator ==(const Vector rhs) const
{
    if (m_x == rhs.m_x && m_y == rhs.m_y && m_z==rhs.m_z)
        return true;
    else
        return false;
}

Vector Vector::abs()
{
    double x{0};
    double y{0};
    double z{0};

    if (m_x < 0.0)
        x=-m_x;
    else
        x=m_x;

    if (m_y < 0.0)
        y=-m_y;
    else
        y=m_y;

    if (m_z < 0.0)
        z=-m_z;
    else
        z=m_z;
    return Vector{x,y,z};
}

double Vector::norm()
{
    return double{sqrt((m_x*m_x)+(m_y*m_y)+(m_z*m_z))};
}

double Vector::dot(Vector rhs)
{
    return double{m_x*rhs.getX()+m_y*rhs.getY()+m_z*rhs.getZ()};
}

Vector Vector::saturate(double min_val, double max_val)
{
    return Vector{saturateNumber(m_x,min_val,max_val),saturateNumber(m_y,min_val,max_val),saturateNumber(m_z,min_val,max_val)};
}

void Vector::setVector(Vector vec)
{
    m_x = vec.getX();
    m_y = vec.getY();
    m_z = vec.getZ();
}

Vector operator +(double lhs, Vector rhs)
{
    return Vector{rhs + lhs};
}

Vector operator *(double lhs, Vector rhs)
{
    return Vector{rhs * lhs};
}

Vector operator -(double lhs, Vector rhs)
{
    return Vector{-rhs + lhs};
}

double saturateNumber(double value, double min_val, double max_val)
{
return double(std::max(std::min(max_val, value),min_val));
}
}


