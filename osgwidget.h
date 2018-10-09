#ifndef MEEN_570_OSGWIDGET
#define MEEN_570_OSGWIDGET

#include <QOpenGLWidget>
//#include <QVector4D>
#include <osg/ref_ptr>
#include <osg/Node>
//#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
//#include <osgText/Text>

class OSGWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  OSGWidget(QWidget* parent = 0,
             Qt::WindowFlags f = 0);

  virtual ~OSGWidget();

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
                           float field_of_view,
                           float min_viewable_range,
                           float max_viewable_range);
  osg::ref_ptr<osgGA::TrackballManipulator> setUpTrackballManipulator(osg::Vec3d camera_location_xyz,
                                                                      osg::Vec3d camera_center_of_focus_xyz,
                                                                      osg::Vec3d world_up_vector_xyz);
  osg::Node* setUpSphere(osg::Vec3 center_of_sphere_xyz,
                         float radius,
                         osg::Vec4 sphere_color_rgba);

  osg::Geode* generateSphereGeode(osg::Vec3 center_of_sphere_xyz,
                             float radius,
                             osg::Vec4 sphere_color_rgba);
  unsigned int getMouseButtonNumber(QMouseEvent* event);
  osg::Node* createWireframeCube(osg::Vec4 &color, osg::Vec3d &scaleFactor);
  void setUpMView(osg::Camera* camera, osg::ref_ptr<osgGA::TrackballManipulator> manipulator);
  void setUpMViewer();

private:
  virtual void on_resize( int width, int height );
  osgGA::EventQueue* getEventQueue() const;
  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> m_graphics_window;
  osg::ref_ptr<osgViewer::CompositeViewer> m_viewer;
  osg::ref_ptr<osgViewer::View> m_view;
  osg::ref_ptr<osg::Group> m_root;
  int m_timer_id{0};
};

#endif
