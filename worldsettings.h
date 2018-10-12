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
    float getDensity();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::WorldSettings *ui;
};

#endif // WORLDSETTINGS_H
