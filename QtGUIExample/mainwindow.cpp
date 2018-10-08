#include "mainwindow.h"
#include "ui_mainwindowform.h"
#include "outputwindow.h"
#include "StuffPanel.h"

#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    mMainWindowUI{new Ui::MainWindowForm}
{
    mMainWindowUI->setupUi(this);

    mDockWidget = new QDockWidget("Output Window",this);
    this->addDockWidget(Qt::BottomDockWidgetArea,mDockWidget);
    mOutputWindow = new OutputWindow(this);
    mDockWidget->setWidget(mOutputWindow);

    mStuffPanel = new StuffPanel(this);
    this->setCentralWidget(mStuffPanel);

    connect(mStuffPanel, SIGNAL(stuff_done(QString)),mOutputWindow,SLOT(print_string(QString)));

}

MainWindow::~MainWindow()
{
    delete mMainWindowUI;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::stuff_done(QString message)
{
    mOutputWindow->print_string(message);
}

