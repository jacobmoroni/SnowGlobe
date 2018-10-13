#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector.h"
#include "sphere.h"

namespace phys {
    class Physics
    {
    public:
        Physics();
        void updatePosition(Sphere *sphere);
        unsigned char checkForCollission(Vector position,
                               Vector box_top_right,
                               Vector box_bottom_left,
                               float radius);
        void bounceOffWallWhenCollisionDetected(Sphere *sphere,
                                                Vector box_top_right,
                                                Vector box_bottom_left);
        void setGravity(Vector gravity);
        Vector getGravity();
        void setDensity(float density);
        float getDensity();
    protected:
        void updateAcceleration(Sphere *sphere);
        void updateVelocity(Sphere *sphere);
        void updateDragForce(Sphere *sphere);
        float m_dt{1/30.0};
        Vector m_gravity{0,0,-9.8};
        float m_density{1.275};
    };
}
#endif // PHYSICS_H
