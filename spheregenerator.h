#ifndef SPHEREGENERATOR_H
#define SPHEREGENERATOR_H

#include <QDialog>
#include "vector.h"

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
    float getRadiusMax();
    float getRadiusMin();
    float getMassMax();
    float getMassMin();
    float getCoeffOfRestitutionMax();
    float getCoeffOfRestitutionMin();
    float getVelMax();
    float getVelMin();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::SphereGenerator *ui;
};

struct SphereGenSettings
{
public:
    int num_spheres{10};
    float rad_max{1};
    float rad_min{.2};
    float mass_max{10};
    float mass_min{2};
    float cr_max{.2};
    float cr_min{1};
    float vel_max{6};
    float vel_min{0};
};


#endif // SPHEREGENERATOR_H
