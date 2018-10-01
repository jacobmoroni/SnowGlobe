#include "osgwidget.h"

#include <osg/Camera>
#include <osg/DisplaySettings>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osgDB/WriteFile>
#include <osgGA/EventQueue>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
#include <osg/LineWidth>
#include <osgUtil/SmoothingVisitor>

#include <osgParticle/FireEffect>

#include <cassert>
#include <vector>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>

OSGWidget::OSGWidget(QWidget* parent, Qt::WindowFlags flags):
    QOpenGLWidget{parent,flags},
    mGraphicsWindow{new osgViewer::GraphicsWindowEmbedded{this->x(),
                                                          this->y(),
                                                          this->width(),
                                                          this->height()}},
    mViewer{new osgViewer::CompositeViewer},
    mRoot{new osg::Group},
    mView{new osgViewer::View}
{
    osg::Vec4 background_color_rgba{1.f, 1.f, 1.f, 1.f}; // predefine colors??
    float field_of_view{45.0};
    float min_viewable_range{1.0};
    float max_viewable_range{1000.0};
    osg::Camera* camera{new osg::Camera};
    this->setUpCamera(camera, background_color_rgba, field_of_view, min_viewable_range, max_viewable_range);

    osg::Vec3d camera_location_xyz{0.0, -20.0, 3.0};
    osg::Vec3d camera_center_of_focus_xyz{0.0, 0.0, 0.0};
    osg::Vec3d world_up_vector_xyz{0.0, 0.0, 1.0};
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator{new osgGA::TrackballManipulator};
    this->setUpTrackballManipulator(manipulator, camera_location_xyz, camera_center_of_focus_xyz, world_up_vector_xyz);

    osg::Vec3 center_of_sphere_xyz{0.f, 0.f, 0.f};
    float radius{2.f};
    osg::Vec4 sphere_color_rgba{0.f, 1.f, 0.f, 0.f}; //predefine colors ??
    this->generateSphere(center_of_sphere_xyz, radius, sphere_color_rgba);
    this->setFocusPolicy(Qt::StrongFocus);
    unsigned int min_width{100};
    unsigned int min_height{100};
    this->setMinimumSize(min_width, min_height);
    this->setMouseTracking(true);
    this->update();
}

OSGWidget::~OSGWidget()
{
}

void OSGWidget::paintEvent(QPaintEvent* /* paintEvent */)
{
    this->makeCurrent();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    this->paintGL();
    painter.end();
    this->doneCurrent();
}

void OSGWidget::paintGL()
{
    mViewer->frame();
}

void OSGWidget::resizeGL(int width, int height)
{
    this->getEventQueue()->windowResize(this->x(), this->y(), width, height);
    mGraphicsWindow->resized(this->x(), this->y(), width, height);
    this->on_resize(width, height);
}

void OSGWidget::keyPressEvent(QKeyEvent* event)
{
    QString keyString   = event->text();
    const char* keyData = keyString.toLocal8Bit().data();

    if(event->key() == Qt::Key_H)
    {
        mView->home();
        return;
    }

    this->getEventQueue()->keyPress( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

void OSGWidget::keyReleaseEvent( QKeyEvent* event )
{
    QString keyString   = event->text();
    const char* keyData = keyString.toLocal8Bit().data();
    this->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGWidget::mouseMoveEvent(QMouseEvent* event)
{
    auto pixelRatio = this->devicePixelRatio();
    this->getEventQueue()->mouseMotion(static_cast<float>(event->x() * pixelRatio),
                                        static_cast<float>(event->y() * pixelRatio));
}

void OSGWidget::mousePressEvent(QMouseEvent* event)
{
    const int leftMouseButton{1};
    const int middleMouseButton{2};
    const int rightMouseButton{3};
    unsigned int button = 0;

    switch(event->button())
    {
    case Qt::LeftButton:
        button = leftMouseButton;
        break;

    case Qt::MiddleButton:
        button = middleMouseButton;
        break;

    case Qt::RightButton:
        button = rightMouseButton;
        break;

    default:
        break;
    }

    auto pixelRatio = this->devicePixelRatio();
    this->getEventQueue()->mouseButtonPress(static_cast<float>(event->x() * pixelRatio),
                                            static_cast<float>(event->y() * pixelRatio),
                                            button);
}

void OSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
    const int leftMouseButton{1};
    const int middleMouseButton{2};
    const int rightMouseButton{3};
    unsigned int button = 0;

    switch(event->button())
    {
    case Qt::LeftButton:
        button = leftMouseButton;
        break;

    case Qt::MiddleButton:
        button = middleMouseButton;
        break;

    case Qt::RightButton:
        button = rightMouseButton;
        break;

    default:
        break;
    }

    auto pixelRatio = this->devicePixelRatio();
    this->getEventQueue()->mouseButtonRelease(static_cast<float>(pixelRatio * event->x()),
                                              static_cast<float>(pixelRatio * event->y()),
                                              button);
}

void OSGWidget::wheelEvent(QWheelEvent* event)
{
    event->accept();
    int delta = event->delta();
    osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?   osgGA::GUIEventAdapter::SCROLL_UP
                                                                 : osgGA::GUIEventAdapter::SCROLL_DOWN;
    this->getEventQueue()->mouseScroll(motion);
}

void OSGWidget::on_resize(int width, int height)
{
    std::vector<osg::Camera*> cameras;
    mViewer->getCameras(cameras);
    auto pixelRatio = this->devicePixelRatio();
    cameras[0]->setViewport(0, 0, width * pixelRatio, height * pixelRatio);
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if(eventQueue)
        return eventQueue;
    else
        throw std::runtime_error("Unable to obtain valid event queue");
}

bool OSGWidget::event(QEvent* event)
{
    bool handled = QOpenGLWidget::event(event);
    repaintOsgGraphicsAfterInteraction(event);
    return handled;
}

void OSGWidget::repaintOsgGraphicsAfterInteraction(QEvent* event)
{
    switch( event->type() )
    {
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    case QEvent::Wheel:
        this->update();
        break;

    default:
        break;
    }
}

void OSGWidget::setUpCamera(osg::Camera* camera, osg::Vec4 background_color, float field_of_view, float min_viewable_range, float max_viewable_range)
{
    float aspectRatio = static_cast<float>(this->width()) / static_cast<float>( this->height());
    auto pixelRatio   = this->devicePixelRatio();
    camera->setViewport(0, 0, this->width() * pixelRatio, this->height() * pixelRatio);
    camera->setClearColor(background_color);
    camera->setProjectionMatrixAsPerspective(field_of_view, aspectRatio, min_viewable_range, max_viewable_range);
    camera->setGraphicsContext(mGraphicsWindow);

    mView->setCamera(camera);
    mView->setSceneData(mRoot.get());
    mView->addEventHandler(new osgViewer::StatsHandler);
}

void OSGWidget::setUpTrackballManipulator(osg::ref_ptr<osgGA::TrackballManipulator> manipulator, osg::Vec3d camera_location_xyz, osg::Vec3d camera_center_of_focus_xyz, osg::Vec3d world_up_vector_xyz)
{
    manipulator->setAllowThrow(false);
    manipulator->setHomePosition(camera_location_xyz, camera_center_of_focus_xyz, world_up_vector_xyz);
    mView->setCameraManipulator(manipulator);
    mViewer->addView(mView);
    mViewer->setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
    mViewer->realize();
    mView->home();
}

void OSGWidget::generateSphere(osg::Vec3 center_of_sphere_xyz, float radius, osg::Vec4 sphere_color_rgba)
{
    osg::Sphere* sphere    = new osg::Sphere{center_of_sphere_xyz, radius};
    osg::ShapeDrawable* sd = new osg::ShapeDrawable{sphere};
    sd->setColor(sphere_color_rgba);
    sd->setName("Sphere");

    osg::Geode* geode = new osg::Geode;
    geode->addDrawable(sd);

    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);

    stateSet->setAttributeAndModes(material, osg::StateAttribute::ON);
    stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

    mRoot->addChild(geode);
}
