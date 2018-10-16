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
    m_main_window_ui{new Ui::MainWindowForm},
    m_sphere_settings{new SphereGenSettings}
{
    m_main_window_ui->setupUi(this);
    this->createToolbar();
}

MainWindow::~MainWindow()
{
    delete m_main_window_ui;
    delete m_sphere_settings;
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
    QAction *home_action = createHomeAction();
    toolBar->addAction(home_action);
    QAction *restart_action = createRestartAction();
    toolBar->addAction(restart_action);
    QAction *clear_action = createClearAction();
    toolBar->addAction(clear_action);
    QAction *generate_action = createGenerateAction();
    toolBar->addAction(generate_action);
    QAction *world_action = createWorldAction();
    toolBar->addAction(world_action);
}

QAction* MainWindow::createStartAction()
{
    const QIcon start_icon = QIcon(":myicons/start.png");
    QAction *start_action = new QAction(start_icon, tr("&Start Simulation (S)"), this);
    start_action->setShortcut(QKeySequence{tr("S")});
    start_action->setStatusTip(tr("Start Simulation (S)"));
    connect(start_action, &QAction::triggered, this, &MainWindow::startSimulation);

    return start_action;
}

QAction* MainWindow::createPauseAction()
{
    const QIcon pause_icon = QIcon(":myicons/pause.png");
    QAction *pause_action = new QAction(pause_icon, tr("&Pause Simulation (P)"), this);
    pause_action->setShortcut(QKeySequence{tr("P")});
    pause_action->setStatusTip(tr("Pause Simulation (P)"));
    connect(pause_action, &QAction::triggered, this, &MainWindow::pauseSimulation);

    return pause_action;
}

QAction* MainWindow::createHomeAction()
{
    const QIcon home_icon = QIcon(":myicons/home.png");
    QAction *home_action = new QAction(home_icon, tr("&Home View (H)"), this);
    home_action->setShortcut(QKeySequence{tr("H")});
    home_action->setStatusTip(tr("Home Simulation (H)"));
    connect(home_action, &QAction::triggered, this, &MainWindow::homeSimulation);

    return home_action;
}

QAction* MainWindow::createRestartAction()
{
    const QIcon restart_icon = QIcon(":myicons/restart.png");
    QAction *restart_action = new QAction(restart_icon, tr("&Restart Simulation (R)"), this);
    restart_action->setShortcut(QKeySequence{tr("R")});
    restart_action->setStatusTip(tr("Restart Simulation (R)"));
    connect(restart_action, &QAction::triggered, this, &MainWindow::restartSimulation);

    return restart_action;
}

QAction* MainWindow::createClearAction()
{
    const QIcon clear_icon = QIcon(":myicons/clear.png");
    QAction *clear_action = new QAction(clear_icon, tr("&Clear Simulation (C)"), this);
    clear_action->setShortcut(QKeySequence{tr("C")});
    clear_action->setStatusTip(tr("Clear Simulation (C)"));
    connect(clear_action, &QAction::triggered, this, &MainWindow::clearSimulation);

    return clear_action;
}

QAction* MainWindow::createGenerateAction()
{
    const QIcon generate_icon = QIcon(":myicons/generate.png");
    QAction *generate_action = new QAction(generate_icon, tr("&Generate Spheres (G)"), this);
    generate_action->setShortcut(QKeySequence{tr("G")});
    generate_action->setStatusTip(tr("Generate Spheres (G)"));
    connect(generate_action, &QAction::triggered, this, &MainWindow::generateSpheres);

    return generate_action;
}

QAction* MainWindow::createWorldAction()
{
    const QIcon world_icon = QIcon(":myicons/world.png");
    QAction *world_action = new QAction(world_icon, tr("&World Settings (W)"), this);
    world_action->setShortcut(QKeySequence{tr("W")});
    world_action->setStatusTip(tr("World Settings (W)"));
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

void MainWindow::homeSimulation()
{
    m_main_window_ui->osg_widget->homeView();
}

void MainWindow::restartSimulation()
{
    m_main_window_ui->osg_widget->restartSimulation();
}

void MainWindow::clearSimulation()
{
    m_main_window_ui->osg_widget->clearSimulation();
}

double MainWindow::forceMax(double max, double min)
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
        m_sphere_settings->num_spheres = sphere_gen->getNumSpheres();

        double rad_max{sphere_gen->getRadiusMax()};
        double rad_min{sphere_gen->getRadiusMin()};
        m_sphere_settings->rad_max = forceMax(rad_max, rad_min);
        m_sphere_settings->rad_min = rad_min;

        double mass_max{sphere_gen->getMassMax()};
        double mass_min{sphere_gen->getMassMin()};
        m_sphere_settings->mass_max = forceMax(mass_max, mass_min);
        m_sphere_settings->mass_min = mass_min;

        double cr_max{sphere_gen->getCoeffOfRestitutionMax()};
        double cr_min{sphere_gen->getCoeffOfRestitutionMin()};
        m_sphere_settings->cr_max = forceMax(cr_max, cr_min);
        m_sphere_settings->cr_min = cr_min;

        double vel_max{sphere_gen->getVelMax()};
        double vel_min{sphere_gen->getVelMin()};
        m_sphere_settings->vel_max = forceMax(vel_max,vel_min);
        m_sphere_settings->vel_min = vel_min;

        m_main_window_ui->osg_widget->generateNewSpheres(m_sphere_settings);
    }
}

void MainWindow::worldSettings()
{
    WorldSettings* settings = new WorldSettings(this);
    if(settings->exec()==QDialog::Accepted)
    {
        phys::Vector gravity{settings->getGravity()};
        double density{settings->getDensity()};
        m_main_window_ui->osg_widget->setWorldSettings(gravity,density);
    }
}
