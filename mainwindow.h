#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include "spheregenerator.h"

class OutputWindow;

namespace Ui
{
class MainWindowForm;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    QAction* createStartAction();
    QAction* createPauseAction();
    QAction* createHomeAction();
    QAction* createRestartAction();
    QAction* createClearAction();
    QAction* createGenerateAction();
    QAction* createWorldAction();
    void createToolbar();
    double forceMax(double max, double min);

public slots:
    void on_actionExit_triggered();
    void startSimulation();
    void pauseSimulation();
    void homeSimulation();
    void restartSimulation();
    void clearSimulation();
    void generateSpheres();
    void worldSettings();

private:
    Ui::MainWindowForm *m_main_window_ui;
    bool m_timer_running{true};
    SphereGenSettings m_sphere_settings;
};

#endif // MAINWINDOW_H
