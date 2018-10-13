#include "physics.h"
#include "vector.h"
#include "sphere.h"

namespace phys {
    Physics::Physics(){}

    void Physics::updateAcceleration(Sphere *sphere)
    {
        this->updateDragForce(sphere);
        sphere->setAcceleration(Vector{m_gravity+(sphere->getDragForce()/sphere->getMass())});
    }

    void Physics::updateVelocity(Sphere *sphere)
    {
        this->updateAcceleration(sphere);
        sphere->setVelocity(Vector{sphere->getVelocity()+(sphere->getAcceleration()*m_dt)});
    }

    void Physics::updatePosition(Sphere *sphere)
    {
        this->updateVelocity(sphere);
        sphere->setPosition(Vector{sphere->getPosition() + sphere->getVelocity()*m_dt});
    }

    void Physics::updateDragForce(Sphere *sphere)
    {
        Vector force{(sphere->getVelocity()*sphere->getVelocity())*0.5*m_density*sphere->getCoeffDrag()*sphere->getArea()};
        force = sphere->getVelocity().sign()*force*-1;
        sphere->setDragForce(force);
    }

    void Physics::bounceOffWallWhenCollisionDetected(Sphere *sphere, Vector box_top_right, Vector box_bottom_left)
    {
        unsigned char collision_detection{checkForCollission(sphere->getPosition(), box_top_right, box_bottom_left, sphere->getRadius())};
        const unsigned char x_wall_pos = 1 << 0;
        const unsigned char x_wall_neg = 1 << 1;
        const unsigned char y_wall_pos = 1 << 2;
        const unsigned char y_wall_neg = 1 << 3;
        const unsigned char z_wall_pos = 1 << 4;
        const unsigned char z_wall_neg = 1 << 5;
        const unsigned char none = 0;
        float overshoot{0.0};
        Vector bounce{1,1,1};

        if (collision_detection & ~none)
        {
            if (collision_detection & x_wall_pos)
            {
                overshoot = box_top_right.getX()-(sphere->getPosition().getX()+sphere->getRadius());
                bounce = bounce*Vector{-1,1,1};
                sphere->setPosition(Vector{sphere->getPosition().getX()+overshoot,sphere->getPosition().getY(),sphere->getPosition().getZ()});
            }
            if (collision_detection & y_wall_pos)
            {
                overshoot = box_top_right.getY()-(sphere->getPosition().getY()+sphere->getRadius());
                bounce = bounce*Vector{1,-1,1};
                sphere->setPosition(Vector{sphere->getPosition().getX(),sphere->getPosition().getY()+overshoot,sphere->getPosition().getZ()});
            }
            if (collision_detection & z_wall_pos)
            {
                overshoot = box_top_right.getZ()-(sphere->getPosition().getZ()+sphere->getRadius());
                bounce = bounce*Vector{1,1,-1};
                sphere->setPosition(Vector{sphere->getPosition().getX(),sphere->getPosition().getY(),sphere->getPosition().getZ()+overshoot});
            }
            if (collision_detection & x_wall_neg)
            {
                overshoot = box_bottom_left.getX()-(sphere->getPosition().getX()-sphere->getRadius());
                bounce = bounce*Vector{-1,1,1};
                sphere->setPosition(Vector{sphere->getPosition().getX()+overshoot,sphere->getPosition().getY(),sphere->getPosition().getZ()});
            }
            if (collision_detection & y_wall_neg)
            {
                overshoot = box_bottom_left.getY()-(sphere->getPosition().getY()-sphere->getRadius());
                bounce = bounce*Vector{1,-1,1};
                sphere->setPosition(Vector{sphere->getPosition().getX(),sphere->getPosition().getY()+overshoot,sphere->getPosition().getZ()});
            }
            if (collision_detection & z_wall_neg)
            {
                overshoot = box_bottom_left.getZ()-(sphere->getPosition().getZ()-sphere->getRadius());
                bounce = bounce*Vector{1,1,-1};
                sphere->setPosition(Vector{sphere->getPosition().getX(),sphere->getPosition().getY(),sphere->getPosition().getZ()+overshoot});
            }
            Vector new_vel{sphere->getVelocity()};
            new_vel = (new_vel*bounce)*sphere->getCoeffRestitution();
            sphere->setVelocity(new_vel);
        }

    }

    unsigned char Physics::checkForCollission(Vector position, Vector box_top_right, Vector box_bottom_left, float radius)
    {
        const unsigned char x_wall_pos = 1 << 0;
        const unsigned char x_wall_neg = 1 << 1;
        const unsigned char y_wall_pos = 1 << 2;
        const unsigned char y_wall_neg = 1 << 3;
        const unsigned char z_wall_pos = 1 << 4;
        const unsigned char z_wall_neg = 1 << 5;

        unsigned char output{0};

        if (position.getX()+radius >= box_top_right.getX())
            output |= x_wall_pos;
        if (position.getX()-radius <= box_bottom_left.getX())
            output |= x_wall_neg;
        if (position.getY()+radius >= box_top_right.getY())
            output |= y_wall_pos;
        if (position.getY()-radius <= box_bottom_left.getY())
            output |= y_wall_neg;
        if (position.getZ()+radius >= box_top_right.getZ())
            output |= z_wall_pos;
        if (position.getZ()-radius <= box_bottom_left.getZ())
            output |= z_wall_neg;

        return output;
    }

    void Physics::setGravity(Vector gravity)
    {
        m_gravity = gravity;
    }

    Vector Physics::getGravity()
    {
        return m_gravity;
    }

    void Physics::setDensity(float density)
    {
        m_density = density;
    }

    float Physics::getDensity()
    {
        return m_density;
    }
}
