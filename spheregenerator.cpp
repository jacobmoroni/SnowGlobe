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

float SphereGenerator::getRadiusMax()
{
    return (float) ui->radius_max->value();
}

float SphereGenerator::getRadiusMin()
{
    return (float) ui->radius_min->value();
}

float SphereGenerator::getMassMax()
{
    return (float) ui->mass_max->value();
}

float SphereGenerator::getMassMin()
{
    return (float) ui->radius_max->value();
}

float SphereGenerator::getCoeffOfRestitutionMax()
{
    return (float) ui->cr_max->value();
}

float SphereGenerator::getCoeffOfRestitutionMin()
{
    return (float) ui->cr_min->value();
}

float SphereGenerator::getVelMax()
{
    return (float) ui->vel_max->value();
}

float SphereGenerator::getVelMin()
{
    return (float) ui->vel_min->value();
}

void SphereGenerator::on_buttonBox_accepted()
{
    QDialog::accept();
}

void SphereGenerator::on_buttonBox_rejected()
{
    QDialog::reject();
}
