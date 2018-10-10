#include "physics.h"
#include "vector.h"
#include "sphere.h"

namespace phys {
    Physics::Physics(){}

    void Physics::updateAcceleration(Vector &accel, Vector drag_force, float mass)
    {
        accel = accel+(drag_force/mass);
    }

    void Physics::updateVelocity(Vector &velocity, Vector &accel, Vector drag_force, float mass)
    {
        this->updateAcceleration(accel, drag_force, mass);
        velocity = velocity+(accel*m_dt);
    }

    void Physics::updatePosition(Vector &position, Vector &velocity, Vector &accel, Vector drag_force, float mass)
    {
        this->updateVelocity(velocity, accel, drag_force, mass);
        position = position + (velocity*m_dt);
    }

    void Physics::bounceOffWallWhenCollisionDetected(Sphere *sphere, Vector box_top_right, Vector box_bottom_left)
    {
        int collision_detection{checkForCollission(sphere->getPosition(), box_top_right, box_bottom_left, sphere->getRadius())};
        const int none{0};
        const int x_wall_pos{1};
        const int y_wall_pos{2};
        const int z_wall_pos{3};
        const int x_wall_neg{4};
        const int y_wall_neg{5};
        const int z_wall_neg{6};
        float overshoot{0.0};

        switch (collision_detection) {
        case x_wall_pos:
            overshoot = box_top_right.getX()-(sphere->getPosition().getX()+sphere->getRadius());
            sphere->setVelocity(-sphere->getCoeffRestitution()*sphere->getVelocity().getX(),
                                sphere->getCoeffRestitution()*sphere->getVelocity().getY(),
                                sphere->getCoeffRestitution()*sphere->getVelocity().getZ());
            sphere->setPosition(sphere->getPosition().getX()+overshoot,sphere->getPosition().getY(),sphere->getPosition().getZ());
            break;
        case y_wall_pos:
            overshoot = box_top_right.getY()-(sphere->getPosition().getY()+sphere->getRadius());
            sphere->setVelocity(sphere->getCoeffRestitution()*sphere->getVelocity().getX(),
                                -sphere->getCoeffRestitution()*sphere->getVelocity().getY(),
                                sphere->getCoeffRestitution()*sphere->getVelocity().getZ());
            sphere->setPosition(sphere->getPosition().getX(),sphere->getPosition().getY()+overshoot,sphere->getPosition().getZ());
            break;
        case z_wall_pos:
            overshoot = box_top_right.getZ()-(sphere->getPosition().getZ()+sphere->getRadius());
            sphere->setVelocity(sphere->getCoeffRestitution()*sphere->getVelocity().getX(),
                                sphere->getCoeffRestitution()*sphere->getVelocity().getY(),
                                -sphere->getCoeffRestitution()*sphere->getVelocity().getZ());
            sphere->setPosition(sphere->getPosition().getX(),sphere->getPosition().getY(),sphere->getPosition().getZ()+overshoot);
            break;
        case x_wall_neg:
            overshoot = box_bottom_left.getX()-(sphere->getPosition().getX()-sphere->getRadius());
            sphere->setVelocity(-sphere->getCoeffRestitution()*sphere->getVelocity().getX(),
                                sphere->getCoeffRestitution()*sphere->getVelocity().getY(),
                                sphere->getCoeffRestitution()*sphere->getVelocity().getZ());
            sphere->setPosition(sphere->getPosition().getX()+overshoot,sphere->getPosition().getY(),sphere->getPosition().getZ());
            break;
        case y_wall_neg:
            overshoot = box_bottom_left.getY()-(sphere->getPosition().getY()-sphere->getRadius());
            sphere->setVelocity(sphere->getCoeffRestitution()*sphere->getVelocity().getX(),
                                -sphere->getCoeffRestitution()*sphere->getVelocity().getY(),
                                sphere->getCoeffRestitution()*sphere->getVelocity().getZ());
            sphere->setPosition(sphere->getPosition().getX(),sphere->getPosition().getY()+overshoot,sphere->getPosition().getZ());
            break;
        case z_wall_neg:
            overshoot = box_bottom_left.getZ()-(sphere->getPosition().getZ()-sphere->getRadius());
            sphere->setVelocity(sphere->getCoeffRestitution()*sphere->getVelocity().getX(),
                                sphere->getCoeffRestitution()*sphere->getVelocity().getY(),
                                -sphere->getCoeffRestitution()*sphere->getVelocity().getZ());
            sphere->setPosition(sphere->getPosition().getX(),sphere->getPosition().getY(),sphere->getPosition().getZ()+overshoot);
            break;
        default:
            break;
        }
    }

    int Physics::checkForCollission(Vector position, Vector box_top_right, Vector box_bottom_left, float radius)
    {
        const int none{0};
        const int x_wall_pos{1};
        const int y_wall_pos{2};
        const int z_wall_pos{3};
        const int x_wall_neg{4};
        const int y_wall_neg{5};
        const int z_wall_neg{6};


        if (position.getX()+radius >= box_top_right.getX())
            return x_wall_pos;
        else if (position.getX()-radius <= box_bottom_left.getX())
            return x_wall_neg;
        else if (position.getY()+radius >= box_top_right.getY())
            return y_wall_pos;
        else if (position.getY()-radius <= box_bottom_left.getY())
            return y_wall_neg;
        else if (position.getZ()+radius >= box_top_right.getZ())
            return z_wall_pos;
        else if (position.getZ()-radius <= box_bottom_left.getZ())
            return z_wall_neg;
        else
            return none;
    }
    float coeff_of_restitution{0.8};
}
