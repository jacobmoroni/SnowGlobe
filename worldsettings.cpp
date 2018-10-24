#include "worldsettings.h"
#include "ui_worldsettings.h"
#include "vector.h"

WorldSettings::WorldSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorldSettings)
{
    ui->setupUi(this);
    ui->gravity_x->setDisabled(true);
    ui->gravity_y->setDisabled(true);
    ui->gravity_z->setDisabled(true);
}

WorldSettings::~WorldSettings()
{
    delete ui;
}

phys::Vector WorldSettings::getGravity()
{
    double grav_x = ui->gravity_x->value();
    double grav_y = ui->gravity_y->value();
    double grav_z = ui->gravity_z->value();
    phys::Vector gravity{grav_x,grav_y,grav_z};
    return gravity;
}

double WorldSettings::getDensity()
{
    double density = ui->density->value();
    return density;
}

bool WorldSettings::getAutogravity()
{
    return m_autogravity;
}

void WorldSettings::on_buttonBox_accepted()
{
    QDialog::accept();
}

void WorldSettings::on_buttonBox_rejected()
{
    QDialog::reject();
}

void WorldSettings::on_checkBox_clicked(bool checked)
{
    if (checked == true)
    {
        m_autogravity = true;
        ui->gravity_x->setDisabled(true);
        ui->gravity_y->setDisabled(true);
        ui->gravity_z->setDisabled(true);
    }
    else
    {
        m_autogravity = false;
        ui->gravity_x->setEnabled(true);
        ui->gravity_y->setEnabled(true);
        ui->gravity_z->setEnabled(true);
    }
}
