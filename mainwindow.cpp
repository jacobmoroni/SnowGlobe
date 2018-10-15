#include "mainwindow.h"
#include "ui_mainwindowform.h"
#include "worldsettings.h"
#include "spheregenerator.h"
#include "vector.h"
#include <QDockWidget>
#include <QToolBar>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    m_main_window_ui{new Ui::MainWindowForm}
{
    m_main_window_ui->setupUi(this);
    this->createToolbar();
}

MainWindow::~MainWindow()
{
    delete m_main_window_ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::createToolbar()
{
   QToolBar *toolBar = addToolBar(tr("My actions"));
   QAction *start_action = createStartAction();
   toolBar->addAction(start_action);
   QAction *pause_action = createPauseAction();
   toolBar->addAction(pause_action);
   QAction *restart_action = createRestartAction();
   toolBar->addAction(restart_action);
   QAction *generate_action = createGenerateAction();
   toolBar->addAction(generate_action);
   QAction *world_action = createWorldAction();
   toolBar->addAction(world_action);
}

QAction* MainWindow::createStartAction()
{
   const QIcon start_icon = QIcon(":myicons/start.png");
   QAction *start_action = new QAction(start_icon, tr("&Run Simulation"), this);
   start_action->setShortcut(QKeySequence{tr("S")});
   start_action->setStatusTip(tr("Run Simulation"));
   connect(start_action, &QAction::triggered, this, &MainWindow::startSimulation);

   return start_action;
}

QAction* MainWindow::createPauseAction()
{
   const QIcon pause_icon = QIcon(":myicons/pause.png");
   QAction *pause_action = new QAction(pause_icon, tr("&Pause Simulation"), this);
   pause_action->setShortcut(QKeySequence{tr("P")});
   pause_action->setStatusTip(tr("Pause Simulation"));
   connect(pause_action, &QAction::triggered, this, &MainWindow::pauseSimulation);

   return pause_action;
}

QAction* MainWindow::createRestartAction()
{
   const QIcon restart_icon = QIcon(":myicons/restart.png");
   QAction *restart_action = new QAction(restart_icon, tr("&Restart Simulation"), this);
   restart_action->setShortcut(QKeySequence{tr("R")});
   restart_action->setStatusTip(tr("Restart Simulation"));
   connect(restart_action, &QAction::triggered, this, &MainWindow::restartSimulation);

   return restart_action;
}

QAction* MainWindow::createGenerateAction()
{
   const QIcon generate_icon = QIcon(":myicons/generate.png");
   QAction *generate_action = new QAction(generate_icon, tr("&Generate Spheres"), this);
   generate_action->setShortcut(QKeySequence{tr("G")});
   generate_action->setStatusTip(tr("Generate Spheres"));
   connect(generate_action, &QAction::triggered, this, &MainWindow::generateSpheres);

   return generate_action;
}

QAction* MainWindow::createWorldAction()
{
   const QIcon world_icon = QIcon(":myicons/world.png");
   QAction *world_action = new QAction(world_icon, tr("&World Settings"), this);
   world_action->setShortcut(QKeySequence{tr("W")});
   world_action->setStatusTip(tr("World Settings"));
   connect(world_action, &QAction::triggered, this, &MainWindow::worldSettings);

   return world_action;
}

void MainWindow::startSimulation()
{
    if (this->m_timer_running==false)
        m_main_window_ui->osg_widget->startMyTimer();
        this->m_timer_running = true;
}

void MainWindow::pauseSimulation()
{
    if (this->m_timer_running==true)
        m_main_window_ui->osg_widget->stopMyTimer();
        this->m_timer_running = false;
}

void MainWindow::restartSimulation()
{
    m_main_window_ui->osg_widget->restartSimulation();
}

float MainWindow::forceMax(float max, float min)
{
    if (min > max)
        return min;
    else
        return max;
}

void MainWindow::generateSpheres()
{
   SphereGenerator* sphere_gen = new SphereGenerator(this);
    if(sphere_gen->exec()==QDialog::Accepted)
    {
        SphereGenValues* sphere_gen_val = new SphereGenValues;
        sphere_gen_val->num_spheres = sphere_gen->getNumSpheres();

        float rad_max{sphere_gen->getRadiusMax()};
        float rad_min{sphere_gen->getRadiusMin()};
        sphere_gen_val->rad_max = forceMax(rad_max, rad_min);
        sphere_gen_val->rad_min = rad_min;

        float mass_max{sphere_gen->getMassMax()};
        float mass_min{sphere_gen->getMassMin()};
        sphere_gen_val->mass_max = forceMax(mass_max, mass_min);
        sphere_gen_val->mass_min = mass_min;

        float cr_max{sphere_gen->getCoeffOfRestitutionMax()};
        float cr_min{sphere_gen->getCoeffOfRestitutionMin()};
        sphere_gen_val->cr_max = forceMax(cr_max, cr_min);
        sphere_gen_val->cr_min = cr_min;

        float vel_max{sphere_gen->getVelMax()};
        float vel_min{sphere_gen->getVelMin()};
        sphere_gen_val->vel_max = forceMax(vel_max,vel_min);
        sphere_gen_val->vel_min = vel_min;

        m_main_window_ui->osg_widget->generateNewSpheres(sphere_gen_val);
        delete sphere_gen_val;
    }
}

void MainWindow::worldSettings()
{
    WorldSettings* settings = new WorldSettings(this);
    if(settings->exec()==QDialog::Accepted)
    {
        phys::Vector gravity{settings->getGravity()};
        float density{settings->getDensity()};
        m_main_window_ui->osg_widget->setWorldSettings(gravity,density);
    }
}
