#ifndef EXPRESSIONDIALOG_H
#define EXPRESSIONDIALOG_H

#include <QDialog>
#include <QEvent>
#include <QTextEdit>
#include <QKeyEvent>
#include <QList>
#include <QChar>
#include <QColor>
#include <QWidget>
#include "Game/Expression.h"
#include "Game/Globals.h"

#define IGNORE_CHANGES_CODE "---"

const QColor INT_CLR    = QColor(0,0,255);
const QColor STR_CLR    = QColor(255,0,0);
const QColor AGI_CLR    = QColor(35,163,0);
const QColor CON_CLR    = QColor(255,111,0);
const QColor SPI_CLR    = QColor(0,255,255);
const QColor HP_CLR     = QColor(171,20,20);
const QColor MP_CLR     = QColor(0,82,166);
const QColor ULVL_CLR   = QColor(252,165,3);
const QColor ALVL_CLR   = QColor(132,255,66);

namespace Ui {
class ExpressionDialog;
}

class ExpressionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpressionDialog(int ID, const char *slot, QString title, QWidget *parent);
    ~ExpressionDialog();

    void setText(QString text);

signals:
    void editingFinished(int ID, QString str);

public slots:
    void updateStyledText();

private slots:
    void on_SaveButton_released();

    void on_CancelButton_released();

    void on_IntButton_released();

    void on_TextEdit_textChanged();

    void on_StrButton_released();

    void on_AgiButton_released();

    void on_ConButton_released();

    void on_SpiButton_released();

    void on_HpButton_released();

    void on_MpButton_released();

    void on_UnitLvlButton_released();

    void on_AbilityLvlButton_released();

    void on_CheckResourceButton_released();

private:
    Ui::ExpressionDialog *ui;

    int ID = -1;
    QString rawText;
    QString styledText;
    bool textBeingUpdated = false;

    int getCursorPosition();
    void setCursorPosition(int pos);
    QString styleRawText(QString text);
    QString colorToStyle(const QColor &color);
    bool eventFilter(QObject *obj, QEvent *event);
    void highlightText();

protected:
    void showEvent(QShowEvent *ev);
};

#endif // ABILITYFIELDEDITDIALOG_H
