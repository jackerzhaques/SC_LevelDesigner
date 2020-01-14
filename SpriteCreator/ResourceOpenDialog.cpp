#include "ResourceOpenDialog.h"
#include "ui_ResourceOpenDialog.h"

ResourceOpenDialog::ResourceOpenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResourceOpenDialog)
{
    ui->setupUi(this);
}

ResourceOpenDialog::~ResourceOpenDialog()
{
    delete ui;
}

void ResourceOpenDialog::on_OkayButton_released()
{
    QString path = "NONE";
    if(ui->LoadedResourceRadio->isChecked()){
        QString str = ui->LoadedResourcesInput->currentText();
        if(str != "NONE"){
            path = "://" + str;
        }
    }
    else if(ui->CustomResourceRadio->isChecked()){
        path = ui->CustomResourceInput->text();
    }

    emit dialogClosed(path);
    this->close();
}

void ResourceOpenDialog::on_CancelButton_released()
{
    this->close();
}

void ResourceOpenDialog::on_LoadedResourcesInput_currentIndexChanged(int)
{
    ui->LoadedResourceRadio->setChecked(true);
}

void ResourceOpenDialog::on_CustomResourceInput_editingFinished()
{
    ui->CustomResourceRadio->setChecked(true);
}
