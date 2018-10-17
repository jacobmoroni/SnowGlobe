#ifndef VECTOR_H
#define VECTOR_H

namespace phys {
class Vector
{
public:
    Vector();
    Vector(double x, double y, double z);
    double getX() const;
    double getY() const;
    double getZ() const;
    Vector sign();
    Vector operator+ (Vector rhs);
    Vector operator- (Vector rhs);
    Vector operator* (Vector rhs);
    Vector operator/ (double number);
    Vector operator* (double number);
    Vector operator+ (double number);
    Vector operator- (double number);
    Vector operator- ();
    bool operator== (const Vector rhs) const;
    Vector abs();
    double norm();
    double dot(Vector rhs);
    void setVector(Vector vec);

private:
    double m_x{0};
    double m_y{0};
    double m_z{0};
};

Vector operator- (double lhs, Vector rhs);
Vector operator+ (double lhs, Vector rhs);
Vector operator* (double lhs, Vector rhs);
}

#endif // VECTOR_H
