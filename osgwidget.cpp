#include "osgwidget.h"

#include <osg/Camera>
#include <osg/Geode>
#include <osg/Material>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osg/PositionAttitudeTransform>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/NodeVisitor>

#include <osgGA/EventQueue>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>

#include <vector>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>
#include "physics.h"
#include "vector.h"
#include "sphere.h"
#include "sphereupdatecallback.h"



void OSGWidget::startMyTimer()
{
    double frames_per_second{30};
    double time_step{1.0/frames_per_second};
    double timer_duration_in_milliseconds{time_step *1000};
    m_timer_id=startTimer(timer_duration_in_milliseconds);
}
void OSGWidget::stopMyTimer()
{
    killTimer(m_timer_id);
}

void OSGWidget::setupWorld()
{
    osg::Vec3 center_of_sphere_xyz{0.f, 0.f, 0.f};
    float sphere_radius{1.f};
    osg::Vec4 sphere_color_rgba{0.f, 1.f, 0.f, 0.f};
    phys::Vector position{0,0,0};
    phys::Vector velocity{7,0,0};
    phys::Vector accel{0,0,-9.8};
    m_sphere = new Sphere(position,
                          velocity,
                          sphere_radius,
                          accel);

    osg::Node* sphere{this->setUpSphere(center_of_sphere_xyz,
                                        sphere_radius,
                                        sphere_color_rgba,
                                        m_sphere)};
    m_root->addChild(sphere);

    osg::Vec4 box_color_rgba(0.f,0.f,0.f,1.f);
    osg::Node* box_transform{this->createWireframeCube(box_color_rgba)};
    m_root->addChild(box_transform);
}

OSGWidget::OSGWidget(QWidget* parent, Qt::WindowFlags flags):
    QOpenGLWidget{parent,flags},
    m_graphics_window{new osgViewer::GraphicsWindowEmbedded{this->x(),
                                                            this->y(),
                                                            this->width(),
                                                            this->height()}},
    m_viewer{new osgViewer::CompositeViewer},
    m_root{new osg::Group},
    m_view{new osgViewer::View}
{
    this->setFocusPolicy(Qt::StrongFocus);
    unsigned int min_width{100};
    unsigned int min_height{100};
    this->setMinimumSize(min_width, min_height);
    this->setMouseTracking(true);

    this->setupMViewer();

//    m_root->addChild(sphere);
    this->setupWorld();

    this->startMyTimer();
}

OSGWidget::~OSGWidget()
{
}

void OSGWidget::timerEvent(QTimerEvent *event)
{
    phys_obj.updatePosition(m_sphere->getPosition(),
                            m_sphere->getVelocity(),
                            m_sphere->getAcceleration(),
                            m_sphere->getDragForce(),
                            m_sphere->getMass());
    phys_obj.bounceOffWallWhenCollisionDetected(m_sphere,phys::Vector{5,5,5},phys::Vector{-5,-5,-5});
    update();
}

void OSGWidget::paintEvent(QPaintEvent*)
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
    m_viewer->frame();
}

void OSGWidget::resizeGL(int width, int height)
{
    this->getEventQueue()->windowResize(this->x(), this->y(), width, height);
    m_graphics_window->resized(this->x(), this->y(), width, height);
    this->on_resize(width, height);
}

void OSGWidget::keyPressEvent(QKeyEvent* event)
{
    QString key_string{event->text()};
    const char* key_data{key_string.toLocal8Bit().data()};

    if(event->key() == Qt::Key_H)
    {
        m_view->home();
        return;
    }

    this->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KeySymbol(*key_data));
}

void OSGWidget::keyReleaseEvent(QKeyEvent* event)
{
    QString key_string{event->text()};
    const char* key_data{key_string.toLocal8Bit().data()};
    this->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KeySymbol(*key_data));
}

void OSGWidget::mouseMoveEvent(QMouseEvent *event)
{
    auto pixel_ratio{this->devicePixelRatio()};
    this->getEventQueue()->mouseMotion(static_cast<float>(event->x() * pixel_ratio),
                                       static_cast<float>(event->y() * pixel_ratio));
}

void OSGWidget::mousePressEvent(QMouseEvent *event)
{
    unsigned int button{this->getMouseButtonNumber(event)};
    auto pixel_ratio{this->devicePixelRatio()};
    this->getEventQueue()->mouseButtonPress(static_cast<float>(event->x() * pixel_ratio),
                                            static_cast<float>(event->y() * pixel_ratio),
                                            button);
}

void OSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
    unsigned int button{this->getMouseButtonNumber(event)};
    auto pixel_ratio{this->devicePixelRatio()};
    this->getEventQueue()->mouseButtonRelease(static_cast<float>(pixel_ratio * event->x()),
                                              static_cast<float>(pixel_ratio * event->y()),
                                              button);
}

void OSGWidget::wheelEvent(QWheelEvent* event)
{
    event->accept();
    int delta{event->delta()};
    osgGA::GUIEventAdapter::ScrollingMotion motion{delta > 0 ?   osgGA::GUIEventAdapter::SCROLL_UP
                                                               : osgGA::GUIEventAdapter::SCROLL_DOWN};
    this->getEventQueue()->mouseScroll(motion);
}

void OSGWidget::on_resize(int width, int height)
{
    std::vector<osg::Camera*> cameras;
    m_viewer->getCameras(cameras);
    auto pixel_ratio{this->devicePixelRatio()};
    int viewport_x{0};
    int viewport_y{0};
    int viewport_width{width * pixel_ratio};
    int viewport_height(height * pixel_ratio);
    cameras[0]->setViewport(viewport_x, viewport_y, viewport_width, viewport_height);
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* event_queue{m_graphics_window->getEventQueue()};

    if(event_queue)
        return event_queue;
    else
        throw std::runtime_error("Unable to obtain valid event queue");
}

bool OSGWidget::event(QEvent* event)
{
    bool handled{QOpenGLWidget::event(event)};
    repaintOsgGraphicsAfterInteraction(event);
    return handled;
}

void OSGWidget::repaintOsgGraphicsAfterInteraction(QEvent* event)
{
    switch(event->type())
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

osg::Camera *OSGWidget::setUpCamera(osg::Vec4 background_color,
                                    float field_of_view,
                                    float min_viewable_range,
                                    float max_viewable_range)
{
    osg::Camera *camera{new osg::Camera};
    float aspect_ratio{static_cast<float>(this->width()) / static_cast<float>( this->height())};
    auto pixel_ratio{this->devicePixelRatio()};
    int viewport_x{0};
    int viewport_y{0};
    int viewport_width{this->width() * pixel_ratio};
    int viewport_height{this->height() * pixel_ratio};
    camera->setViewport(viewport_x, viewport_y, viewport_width, viewport_height);
    camera->setClearColor(background_color);
    camera->setProjectionMatrixAsPerspective(field_of_view, aspect_ratio, min_viewable_range, max_viewable_range);
    camera->setGraphicsContext(m_graphics_window);

    return camera;
}

osg::ref_ptr<osgGA::TrackballManipulator> OSGWidget::setUpTrackballManipulator(osg::Vec3d camera_location_xyz,
                                                                               osg::Vec3d camera_center_of_focus_xyz,
                                                                               osg::Vec3d world_up_vector_xyz)
{
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator{new osgGA::TrackballManipulator};
    manipulator->setAllowThrow(false);
    manipulator->setHomePosition(camera_location_xyz, camera_center_of_focus_xyz, world_up_vector_xyz);

    return manipulator;
}

osg::Node *OSGWidget::setUpSphere(osg::Vec3 center_of_sphere_xyz,
                                  float radius,
                                  osg::Vec4 sphere_color_rgba,
                                  Sphere *sphere)
{
    osg::Geode* sphere_geode{this->generateSphereGeode(center_of_sphere_xyz,
                                           radius,
                                           sphere_color_rgba)};

    osg::PositionAttitudeTransform *transform{new osg::PositionAttitudeTransform};
    transform->setPosition(center_of_sphere_xyz);
    transform->setUpdateCallback(new SphereUpdateCallback{m_sphere});
    transform->addChild(sphere_geode);
    return transform;
}

osg::Geode *OSGWidget::generateSphereGeode(osg::Vec3 center_of_sphere_xyz,
                                      float radius,
                                      osg::Vec4 sphere_color_rgba)
{
    osg::Sphere* sphere{new osg::Sphere{center_of_sphere_xyz, radius}};
    osg::ShapeDrawable* sd{new osg::ShapeDrawable{sphere}};
    sd->setColor(sphere_color_rgba);
    sd->setName("Sphere");

    osg::Geode* geode{new osg::Geode};
    geode->addDrawable(sd);

    osg::StateSet* state_set{geode->getOrCreateStateSet()};
    osg::Material* material{new osg::Material};
    material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    state_set->setAttributeAndModes(material, osg::StateAttribute::ON);
    state_set->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

    return geode;
}

unsigned int OSGWidget::getMouseButtonNumber(QMouseEvent* event)
{
    unsigned int left_mouse_button{1};
    unsigned int middle_mouse_button{2};
    unsigned int right_mouse_button{3};
    unsigned int button{0};

    switch(event->button())
    {
    case Qt::LeftButton:
        button = left_mouse_button;
        break;

    case Qt::MiddleButton:
        button = middle_mouse_button;
        break;

    case Qt::RightButton:
        button = right_mouse_button;
        break;

    default:
        break;
    }

    return button;
}


osg::Node *OSGWidget::createWireframeCube(osg::Vec4 &color)
{
    osg::Vec3Array* v = new osg::Vec3Array;
    v->resize( 8 );
    (*v)[0].set( 5.f, 5.f, -5.f );
    (*v)[1].set(-5.f, 5.f, -5.f );
    (*v)[2].set(-5.f, -5.f, -5.f );
    (*v)[3].set(5.f, -5.f, -5.f );
    (*v)[4].set(5.f, 5.f, 5.f );
    (*v)[5].set(-5.f, 5.f, 5.f );
    (*v)[6].set(-5.f, -5.f, 5.f );
    (*v)[7].set(5.f, -5.f, 5.f );

    osg::Geometry* geom = new osg::Geometry;
    geom->setUseDisplayList( false );
    geom->setVertexArray( v );

    osg::Vec4Array* c = new osg::Vec4Array;
    c->push_back( color );
    geom->setColorArray( c, osg::Array::BIND_OVERALL );

    GLushort idxLines[8] = {0, 4, 1, 5, 2, 6, 3, 7};
    GLushort idxLoop1[4] = {0, 1, 2, 3};
    GLushort idxLoop2[4] = {4, 5, 6, 7};

    geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINES, 8, idxLines ) );
    geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINE_LOOP, 4, idxLoop1 ) );
    geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINE_LOOP, 4, idxLoop2 ) );

    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( geom );

    geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );
    geode->getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    osg::PositionAttitudeTransform* transform = new osg::PositionAttitudeTransform;

    osg::Vec3d scaleFactor(1.0,1.0,1.0);
    transform->setScale(scaleFactor);

    transform->addChild(geode);
    return transform;
}

void OSGWidget::setUpMView()
{
    osg::Vec4 background_color_rgba{1.f, 1.f, 1.f, 1.f};
    float field_of_view{45.0};
    float min_viewable_range{1.0};
    float max_viewable_range{1000.0};
    osg::Camera* camera{this->setUpCamera(background_color_rgba,
                                          field_of_view,
                                          min_viewable_range,
                                          max_viewable_range)};

    osg::Vec3d camera_location_xyz{0.0, -20.0, 3.0};
    osg::Vec3d camera_center_of_focus_xyz{0.0, 0.0, 0.0};
    osg::Vec3d world_up_vector_xyz{0.0, 0.0, 1.0};
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator{this->setUpTrackballManipulator(camera_location_xyz,
                                                                                          camera_center_of_focus_xyz,
                                                                                          world_up_vector_xyz)};
    m_view->setCamera(camera);
    m_view->setCameraManipulator(manipulator);
    m_view->setSceneData(m_root.get());
    m_view->addEventHandler(new osgViewer::StatsHandler);
    m_view->home();
}

void OSGWidget::setupMViewer()
{
    this->setUpMView();
    m_viewer->addView(m_view);
    m_viewer->setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
    m_viewer->realize();
}
