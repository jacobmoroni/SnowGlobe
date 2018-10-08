#include "stuffpanel.h"
#include "ui_stuffpanel.h"
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QDoubleValidator>

StuffPanel::StuffPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuffPanel)
{
    ui->setupUi(this);

    QDoubleValidator* doubleValidator = new QDoubleValidator;
    ui->initialVelocity->setValidator(doubleValidator);
}

StuffPanel::~StuffPanel()
{
    delete ui;
}
void StuffPanel::on_colorButton_clicked()
{
    QColor color = QColorDialog::getColor();
    ui->selectedColor->setText(color.name());
    ui->selectedColor->setPalette(QPalette(color));
    ui->selectedColor->setAutoFillBackground(true);
}

void StuffPanel::on_printData_clicked()
{
    QString message;
    message="Color "+ui->selectedColor->text()+"\n";
    message+="Initial Velocity "+ui->initialVelocity->text()+"\n";
    emit(stuff_done(message));
}
