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
    void createToolbar();
public slots:
    void on_actionExit_triggered();
    void startSimulation();
    void pauseSimulation();

private:
    Ui::MainWindowForm *m_main_window_ui;

};

#endif // MAINWINDOW_H
