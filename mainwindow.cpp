#include "mainwindow.h"
#include "ui_mainwindowform.h"
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
}

QAction* MainWindow::createStartAction()
{
   const QIcon start_icon = QIcon(":myicons/start.png");
   QAction *start_action = new QAction(start_icon, tr("&Run Simulation"), this);
   start_action->setShortcut(QKeySequence{tr("Ctrl+R")});
   start_action->setStatusTip(tr("Run Simulation"));
   connect(start_action, &QAction::triggered, this, &MainWindow::startSimulation);

   return start_action;
}

QAction* MainWindow::createPauseAction()
{
   const QIcon pause_icon = QIcon(":myicons/pause.png");
   QAction *pause_action = new QAction(pause_icon, tr("&Pause Simulation"), this);
   pause_action->setShortcut(QKeySequence{tr("Ctrl+P")});
   pause_action->setStatusTip(tr("Pause Simulation"));
   connect(pause_action, &QAction::triggered, this, &MainWindow::pauseSimulation);

   return pause_action;
}

void MainWindow::startSimulation()
{
   m_main_window_ui->osg_widget->startMyTimer();
}

void MainWindow::pauseSimulation()
{
   m_main_window_ui->osg_widget->stopMyTimer();
}
