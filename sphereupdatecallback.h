#ifndef SPHEREUPDATECALLBACK_H
#define SPHEREUPDATECALLBACK_H

#include <osg/NodeCallback>
#include "sphere.h"

class SphereUpdateCallback: public osg::NodeCallback
{
public:
    SphereUpdateCallback(Sphere* sphere);

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
private:
    Sphere* m_sphere{nullptr};
};

#endif // SPHEREUPDATECALLBACK_H
