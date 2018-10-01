#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>

class OutputWindow;
//class OSGWidget; //added this

namespace Ui {
class MainWindowForm;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_actionExit_triggered();
private:
    Ui::MainWindowForm *mMainWindowUI;
//    OSGWidget* mOSGWidget{nullptr}; //added this
};

#endif // MAINWINDOW_H
