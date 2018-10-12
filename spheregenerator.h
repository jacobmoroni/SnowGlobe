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

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::SphereGenerator *ui;
};

#endif // SPHEREGENERATOR_H
