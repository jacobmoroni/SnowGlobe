#include "worldsettings.h"
#include "ui_worldsettings.h"
#include "vector.h"

WorldSettings::WorldSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorldSettings)
{
    ui->setupUi(this);
}

WorldSettings::~WorldSettings()
{
    delete ui;
}

phys::Vector WorldSettings::getGravity()
{
    float grav_x = (float) ui->gravity_x->value();
    float grav_y = (float) ui->gravity_y->value();
    float grav_z = (float) ui->gravity_z->value();
    phys::Vector gravity{grav_x,grav_y,grav_z};
    return gravity;
}

float WorldSettings::getDensity()
{
    float density = (float) ui->density->value();
    return density;
}

void WorldSettings::on_buttonBox_accepted()
{
    QDialog::accept();
}

void WorldSettings::on_buttonBox_rejected()
{
    QDialog::reject();
}
