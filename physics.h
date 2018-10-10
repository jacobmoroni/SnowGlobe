#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector.h"
#include "sphere.h"

namespace phys {
    class Physics
    {
    public:
        Physics();
        void updatePosition(Vector &position,
                            Vector &velocity,
                            Vector &accel,
                            Vector drag_force,
                            float mass);
        int checkForCollission(Vector position,
                               Vector box_top_right,
                               Vector box_bottom_left,
                               float radius);
        void bounceOffWallWhenCollisionDetected(Sphere *sphere, Vector box_top_right, Vector box_bottom_left);

    protected:
        void updateAcceleration(Vector &accel,
                                Vector drag_force,
                                float mass);

        void updateVelocity(Vector &velocity,
                            Vector &accel,
                            Vector drag_force,
                            float mass);
        float m_dt{1/30.0};
    };
}
#endif // PHYSICS_H
