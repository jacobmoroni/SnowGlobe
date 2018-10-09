#ifndef VECTOR_H
#define VECTOR_H

namespace phys {
    class Vector
    {
    public:
        Vector();
        Vector(double x, double y, double z);
        Vector operator+ (Vector rhs);
        Vector operator- (Vector rhs);
        Vector operator* (float number);
        Vector operator- ();
        bool operator== (Vector rhs);
        double getX() const;
        double getY() const;
        double getZ() const;

    private:
        double m_x{0};
        double m_y{0};
        double m_z{0};
    };
}
#endif // VECTOR_H
