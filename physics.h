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
        int checkForCollission(Vector position,
                               Vector box_top_right,
                               Vector box_bottom_left,
                               float radius);

        void bounceOffWallWhenCollisionDetected(Sphere *sphere,
                                                Vector box_top_right,
                                                Vector box_bottom_left);

    protected:
        void updateAcceleration(Sphere *sphere);
        void updateVelocity(Sphere *sphere);
        float m_dt{1/30.0};
    };
}
#endif // PHYSICS_H
