#ifndef RESOURCEOPENDIALOG_H
#define RESOURCEOPENDIALOG_H

#include <QDialog>

namespace Ui {
class ResourceOpenDialog;
}

class ResourceOpenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResourceOpenDialog(QWidget *parent = nullptr);
    ~ResourceOpenDialog();

signals:
    void dialogClosed(QString path);

private slots:
    void on_OkayButton_released();

    void on_CancelButton_released();

    void on_LoadedResourcesInput_currentIndexChanged(int index);

    void on_CustomResourceInput_editingFinished();

private:
    Ui::ResourceOpenDialog *ui;
};

#endif // RESOURCEOPENDIALOG_H
