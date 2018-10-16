#include "spheregenerator.h"
#include "ui_spheregenerator.h"
#include "vector.h"

SphereGenerator::SphereGenerator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SphereGenerator)
{
    ui->setupUi(this);
}

SphereGenerator::~SphereGenerator()
{
    delete ui;
}

int SphereGenerator::getNumSpheres()
{
    return ui->num_spheres->value();
}

double SphereGenerator::getRadiusMax()
{
    return ui->radius_max->value();
}

double SphereGenerator::getRadiusMin()
{
    return ui->radius_min->value();
}

double SphereGenerator::getMassMax()
{
    return ui->mass_max->value();
}

double SphereGenerator::getMassMin()
{
    return ui->radius_max->value();
}

double SphereGenerator::getCoeffOfRestitutionMax()
{
    return ui->cr_max->value();
}

double SphereGenerator::getCoeffOfRestitutionMin()
{
    return ui->cr_min->value();
}

double SphereGenerator::getVelMax()
{
    return ui->vel_max->value();
}

double SphereGenerator::getVelMin()
{
    return ui->vel_min->value();
}

void SphereGenerator::on_buttonBox_accepted()
{
    QDialog::accept();
}

void SphereGenerator::on_buttonBox_rejected()
{
    QDialog::reject();
}

void SphereGenerator::on_vel_min_valueChanged(double value)
{
    m_settings.vel_min = value;
    if (m_settings.vel_max <= m_settings.vel_min)
        ui->vel_max->setValue(m_settings.vel_min);
}

void SphereGenerator::on_vel_max_valueChanged(double value)
{
    m_settings.vel_max = value;
    if (m_settings.vel_max <= m_settings.vel_min)
        ui->vel_min->setValue(m_settings.vel_max);
}

void SphereGenerator::on_cr_min_valueChanged(double value)
{
    m_settings.cr_min = value;
    if (m_settings.cr_max <= m_settings.cr_min)
        ui->cr_max->setValue(m_settings.cr_min);
}

void SphereGenerator::on_cr_max_valueChanged(double value)
{
    m_settings.cr_max = value;
    if (m_settings.cr_max <= m_settings.cr_min)
        ui->cr_min->setValue(m_settings.cr_max);
}

void SphereGenerator::on_mass_min_valueChanged(double value)
{
    m_settings.mass_min = value;
    if (m_settings.mass_max <= m_settings.mass_min)
        ui->mass_max->setValue(m_settings.mass_min);
}

void SphereGenerator::on_mass_max_valueChanged(double value)
{
    m_settings.mass_max = value;
    if (m_settings.mass_max <= m_settings.mass_min)
        ui->mass_min->setValue(m_settings.mass_max);
}

void SphereGenerator::on_radius_min_valueChanged(double value)
{
    m_settings.rad_min = value;
    if (m_settings.rad_max <= m_settings.rad_min)
        ui->radius_max->setValue(m_settings.rad_min);
}

void SphereGenerator::on_radius_max_valueChanged(double value)
{
    m_settings.rad_max = value;
    if (m_settings.rad_max <= m_settings.rad_min)
        ui->radius_min->setValue(m_settings.rad_max);
}
