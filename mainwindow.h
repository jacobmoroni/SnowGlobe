#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>

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
    QAction* createRestartAction();
    QAction* createGenerateAction();
    QAction* createWorldAction();
    void createToolbar();
    float forceMax(float max, float min);

public slots:
    void on_actionExit_triggered();
    void startSimulation();
    void pauseSimulation();
    void restartSimulation();
    void generateSpheres();
    void worldSettings();

private:
    Ui::MainWindowForm *m_main_window_ui;
    bool m_timer_running{true};
};

#endif // MAINWINDOW_H
