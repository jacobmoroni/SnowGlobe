#ifndef WORLDSETTINGS_H
#define WORLDSETTINGS_H

#include <QDialog>
#include "vector.h"

namespace Ui {
class WorldSettings;
}

class WorldSettings : public QDialog
{
    Q_OBJECT

public:
    explicit WorldSettings(QWidget *parent = nullptr);
    ~WorldSettings();

    phys::Vector getGravity();
    double getDensity();
    bool getAutogravity();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();    
    void on_checkBox_clicked(bool checked);

private:
    Ui::WorldSettings *ui;
    bool m_autogravity{true};
};

#endif // WORLDSETTINGS_H
