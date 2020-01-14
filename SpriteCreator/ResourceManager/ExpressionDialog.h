#ifndef ABILITYFIELDEDITDIALOG_H
#define ABILITYFIELDEDITDIALOG_H

#include <QDialog>

namespace Ui {
class AbilityFieldEditDialog;
}

class AbilityFieldEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AbilityFieldEditDialog(QWidget *parent = nullptr);
    ~AbilityFieldEditDialog();

private:
    Ui::AbilityFieldEditDialog *ui;
};

#endif // ABILITYFIELDEDITDIALOG_H
