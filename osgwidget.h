#ifndef MEEN_570_OSGWIDGET
#define MEEN_570_OSGWIDGET

#include <QOpenGLWidget>
#include <osg/ref_ptr>
#include <osg/Camera>
#include <osg/Geode>
#include <osg/Node>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <vector>
#include "vector.h"
#include "physics.h"
#include "sphere.h"
#include "spheregenerator.h"

class OSGWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OSGWidget(QWidget* parent = 0,
              Qt::WindowFlags f = 0);

    virtual ~OSGWidget();
    void startMyTimer();
    void stopMyTimer();
    void setWorldSettings(phys::Vector gravity, double density);
    void setAutogravity(bool autogravity);
    void generateNewSpheres(SphereGenSettings sphere_gen_vals);
    void restartSimulation();
    void clearSimulation();
    void homeView();

protected:
    void timerEvent(QTimerEvent *event);
    virtual void paintEvent(QPaintEvent* paintEvent);
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);

    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual bool event(QEvent* event);
    void repaintOsgGraphicsAfterInteraction(QEvent* event);

    osg::Camera* setUpCamera(osg::Vec4 background_color_rgba,
                             double field_of_view,
                             double min_viewable_range,
                             double max_viewable_range);
    osg::ref_ptr<osgGA::TrackballManipulator> setUpTrackballManipulator(osg::Vec3d camera_location_xyz,
                                                                        osg::Vec3d camera_center_of_focus_xyz,
                                                                        osg::Vec3d world_up_vector_xyz);
    osg::Node* setUpSphere(osg::Vec3 center_of_sphere_xyz,
                           double radius,
                           osg::Vec4 sphere_color_rgba,
                           Sphere *sphere);

    osg::Geode* generateSphereGeode(osg::Vec3 center_of_sphere_xyz,
                                    double radius,
                                    osg::Vec4 sphere_color_rgba);
    unsigned int getMouseButtonNumber(QMouseEvent* event);
    osg::Node* createWireframeCube(osg::Vec4 &color, double box_size);
    void setUpMView();
    void setupMViewer();
    void setupWorld();
    double randomDouble(double min, double max);
    void updateAutogravity();

private:
    virtual void on_resize(int width, int height);
    osgGA::EventQueue* getEventQueue() const;
    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> m_graphics_window;
    osg::ref_ptr<osgViewer::CompositeViewer> m_viewer;
    osg::ref_ptr<osgViewer::View> m_view;
    osg::ref_ptr<osg::Group> m_root;
    int m_timer_id{0};
    phys::Physics m_phys_obj;
    std::vector<Sphere*> m_spheres;
    std::vector<osg::Node*> m_sphere_geodes;
    double m_box_size{5};
    SphereGenSettings m_sphere_settings;
    osg::Quat m_q0;
    osg::ref_ptr<osgGA::TrackballManipulator> m_manipulator;
    bool m_autogravity{false};
};

#endif
