#ifndef VECTOR_H
#define VECTOR_H

namespace phys {
    class Vector
    {
    public:
        Vector();
        Vector(float x, float y, float z);
        float getX() const;
        float getY() const;
        float getZ() const;
        Vector operator+ (Vector rhs);
        Vector operator- (Vector rhs);
        Vector operator/ (float number);
        Vector operator* (float number);
        Vector operator+ (float number);
        Vector operator- (float number);
        Vector operator- ();
        bool operator== (const Vector rhs) const;
        Vector abs();
        void setVector(Vector vec);

    private:
        float m_x{0};
        float m_y{0};
        float m_z{0};
    };
}
#endif // VECTOR_H
