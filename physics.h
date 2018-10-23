#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector.h"
#include <vector>
#include "sphere.h"

namespace phys {
class Physics
{
public:
    Physics();
    void updatePosition(Sphere *sphere);
    unsigned char checkForBoxCollission(Vector position, Vector box_top_right, Vector box_bottom_left, double radius);
    void bounceOffWall(Sphere *sphere, Vector box_top_right, Vector box_bottom_left);
    void setGravity(Vector gravity);
    Vector getGravity();
    void setDensity(double density);
    double getDensity();
    void checkForSphereCollision(std::vector<Sphere *> &spheres);
    void bounceOffSphere(Sphere *sphere1, Sphere *sphere2);
    void adjustPositionAfterBounce(Sphere *sphere1, Sphere *sphere2);
protected:    
    void updateAcceleration(Sphere *sphere);
    void updateVelocity(Sphere *sphere);
    void updateDragForce(Sphere *sphere);
    double m_dt{1/30.0};
    Vector m_gravity{0,0,-9.8};
    double m_density{1.275};
    double m_collision_buffer{0.01};
    double m_max_drag_force{50000};
};
}
#endif // PHYSICS_H
