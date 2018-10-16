#include "vector.h"
#include <math.h>

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

Vector Vector::sign()
{
    double x{(this->getX() > 0.f) ? 1.f : ((this->getX() < 0.f) ? -1.f : 0.f)};
    double y{(this->getY() > 0.f) ? 1.f : ((this->getY() < 0.f) ? -1.f : 0.f)};
    double z{(this->getZ() > 0.f) ? 1.f : ((this->getZ() < 0.f) ? -1.f : 0.f)};

    return Vector{x,y,z};
}

Vector Vector::operator +(Vector rhs)
{
    return Vector{this->m_x + rhs.m_x, this->m_y + rhs.m_y, this->m_z + rhs.m_z};
}

Vector Vector::operator -(Vector rhs)
{
    return Vector{this->m_x - rhs.m_x, this->m_y - rhs.m_y, this->m_z - rhs.m_z};
}

Vector Vector::operator *(Vector rhs)
{
    return Vector{this->m_x*rhs.getX(), this->m_y*rhs.getY(), this->m_z*rhs.getZ()};
}
Vector Vector::operator /(double number)
{
    return Vector{this->m_x/number,this->m_y/number,this->m_z/number};
}

Vector Vector::operator *(double number)
{
    return Vector{this->m_x*number, this->m_y*number, this->m_z*number};
}

Vector Vector::operator +(double number)
{
    return Vector{this->m_x+number, this->m_y+number, this->m_z+number};
}

Vector Vector::operator -(double number)
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

Vector Vector::abs()
{
    double x{0};
    double y{0};
    double z{0};

    if (this->getX() < 0.0)
        x=-this->getX();
    else
        x=this->getX();

    if (this->getY() < 0.0)
        y=-this->getY();
    else
        y=this->getY();

    if (this->getZ() < 0.0)
        z=-this->getZ();
    else
        z=this->getZ();
    return Vector{x,y,z};
}

double Vector::norm()
{
    return double{(double)sqrt((this->m_x*this->m_x)+(this->m_y*this->m_y)+(this->m_z*this->m_z))};
}

void Vector::setVector(Vector vec)
{
    this->m_x = vec.getX();
    this->m_y = vec.getY();
    this->m_z = vec.getZ();
}
}
