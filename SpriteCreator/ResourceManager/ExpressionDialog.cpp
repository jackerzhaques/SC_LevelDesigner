#include "AbilityFieldEditDialog.h"
#include "ui_AbilityFieldEditDialog.h"

AbilityFieldEditDialog::AbilityFieldEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AbilityFieldEditDialog)
{
    ui->setupUi(this);
}

AbilityFieldEditDialog::~AbilityFieldEditDialog()
{
    delete ui;
}
