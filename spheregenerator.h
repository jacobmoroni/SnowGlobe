#ifndef SPHEREGENERATOR_H
#define SPHEREGENERATOR_H

#include <QDialog>
#include "vector.h"

struct SphereGenSettings
{
public:
    int num_spheres{10};
    double rad_max{1};
    double rad_min{.2};
    double mass_max{10};
    double mass_min{2};
    double cr_max{.2};
    double cr_min{1};
    double vel_max{6};
    double vel_min{0};
};

namespace Ui {
class SphereGenerator;
}

class SphereGenerator : public QDialog
{
    Q_OBJECT

public:
    explicit SphereGenerator(QWidget *parent = nullptr);
    ~SphereGenerator();

    int getNumSpheres();
    double getRadiusMax();
    double getRadiusMin();
    double getMassMax();
    double getMassMin();
    double getCoeffOfRestitutionMax();
    double getCoeffOfRestitutionMin();
    double getVelMax();
    double getVelMin();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_vel_min_valueChanged(double value);
    void on_vel_max_valueChanged(double value);
    void on_cr_min_valueChanged(double value);
    void on_cr_max_valueChanged(double value);
    void on_mass_min_valueChanged(double value);
    void on_mass_max_valueChanged(double value);
    void on_radius_min_valueChanged(double value);
    void on_radius_max_valueChanged(double value);
private:
    Ui::SphereGenerator *ui;
    SphereGenSettings m_settings;
};

#endif // SPHEREGENERATOR_H
