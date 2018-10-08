#ifndef STUFFPANEL_H
#define STUFFPANEL_H

#include <QWidget>

namespace Ui {
class StuffPanel;
}

class StuffPanel : public QWidget
{
    Q_OBJECT

public:
    explicit StuffPanel(QWidget *parent = nullptr);
    ~StuffPanel();
signals:
    void stuff_done(QString);

public slots:
    void on_colorButton_clicked();
    void on_printData_clicked();
private:
    Ui::StuffPanel *ui;
};

#endif // STUFFPANEL_H
