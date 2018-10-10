#include "sphereupdatecallback.h"
#include "vector.h"
#include "sphere.h"
#include <osg/PositionAttitudeTransform>

SphereUpdateCallback::SphereUpdateCallback(Sphere *sphere): m_sphere{sphere} {}

void SphereUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
    osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    phys::Vector pos{m_sphere->getPosition()};

    pat->setPosition(osg::Vec3{pos.getX(),pos.getY(),pos.getZ()});

    traverse(node, nv);
}
