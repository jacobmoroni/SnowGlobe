#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>

class OutputWindow;
class StuffPanel;


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
    void stuff_done(QString message);
private:
    Ui::MainWindowForm *mMainWindowUI;
    QDockWidget* mDockWidget;
    OutputWindow* mOutputWindow;
    StuffPanel* mStuffPanel;

};

#endif // MAINWINDOW_H
