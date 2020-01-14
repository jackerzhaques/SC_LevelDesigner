#include "ExpressionDialog.h"
#include "ui_ExpressionDialog.h"

#include <QDebug>

ExpressionDialog::ExpressionDialog(int ID, const char *slot, QString title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpressionDialog)
{
    ui->setupUi(this);
    ui->TextEdit->installEventFilter(this);
    this->setWindowTitle(title);
    this->ID = ID;

    connect(this, SIGNAL(editingFinished(int, QString)), parent, slot);
}

ExpressionDialog::~ExpressionDialog()
{
    delete ui;
}

void ExpressionDialog::setText(QString text)
{
    this->rawText = text;
    updateStyledText();
    this->setCursorPosition(ui->TextEdit->toPlainText().size() - 1);
}

void ExpressionDialog::updateStyledText()
{
    //Save the cursor to be restored later
    int cursorPos = getCursorPosition();

    //Restyle the plain text
    styledText = styleRawText(rawText);
    ui->TextEdit->setHtml(styledText);

    //Restore the cursor
    this->setCursorPosition(cursorPos);
}

void ExpressionDialog::on_SaveButton_released()
{
    emit editingFinished(ID, this->rawText);
    this->hide();
}

void ExpressionDialog::on_CancelButton_released()
{
    emit editingFinished(ID, IGNORE_CHANGES_CODE);    //Send a special code that says "Ignore these changes"
    this->hide();
}

int ExpressionDialog::getCursorPosition()
{
    return ui->TextEdit->textCursor().position();
}

void ExpressionDialog::setCursorPosition(int pos)
{
    if(pos > 0 && pos < ui->TextEdit->toPlainText().size()){
        QTextCursor cursor = ui->TextEdit->textCursor();
        cursor.setPosition(pos);
        ui->TextEdit->setTextCursor(cursor);
    }
}

QString ExpressionDialog::styleRawText(QString text)
{
    text.replace(INT_TEXT, colorToStyle(INT_CLR));
    text.replace(STR_TEXT, colorToStyle(STR_CLR));
    text.replace(AGI_TEXT, colorToStyle(AGI_CLR));
    text.replace(CON_TEXT, colorToStyle(CON_CLR));
    text.replace(SPI_TEXT, colorToStyle(SPI_CLR));
    text.replace(HP_TEXT, colorToStyle(HP_CLR));
    text.replace(MP_TEXT, colorToStyle(MP_CLR));
    text.replace(ULVL_TEXT, colorToStyle(ULVL_CLR));
    text.replace(ALVL_TEXT, colorToStyle(ALVL_CLR));
    text.replace("\n", "<br />");

    return text;
}

QString ExpressionDialog::colorToStyle(const QColor &color)
{
    QString str = "<span style='color: rgb(%1,%2,%3)'>%4</span>";
    str = str.arg(color.red()).arg(color.green()).arg(color.blue());

    if(color == INT_CLR){
        str = str.arg("[INT]");
    }
    else if(color == STR_CLR){
        str = str.arg("[STR]");
    }
    else if(color == AGI_CLR){
        str = str.arg("[AGI]");
    }
    else if(color == CON_CLR){
        str = str.arg("[CON]");
    }
    else if(color == SPI_CLR){
        str = str.arg("[SPI]");
    }
    else if(color == HP_CLR){
        str = str.arg("[HP]");
    }
    else if(color == MP_CLR){
        str = str.arg("[MP]");
    }
    else if(color == ULVL_CLR){
        str = str.arg("[ULVL]");
    }
    else if(color == ALVL_CLR){
        str = str.arg("[ALVL]");
    }
    else{
        //Invalid case
    }

    return str;
}

bool ExpressionDialog::eventFilter(QObject *obj, QEvent *event)
{
    //Only filter events for the text edit
    if(obj == ui->TextEdit &&
        QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier) &&
        event->type() == QEvent::KeyPress)
    {
        auto keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return){
            on_SaveButton_released();
            return true;
        }
    }
    return false;
}

void ExpressionDialog::highlightText()
{
    ui->TextEdit->selectAll();
    ui->TextEdit->setFocus();
}

void ExpressionDialog::showEvent(QShowEvent *ev)
{
    QDialog::showEvent(ev);
    highlightText();
}

void ExpressionDialog::on_TextEdit_textChanged()
{
    if(!textBeingUpdated){
        textBeingUpdated = true;
        this->rawText = ui->TextEdit->toPlainText();
        this->updateStyledText();
        textBeingUpdated = false;
    }
}

void ExpressionDialog::on_IntButton_released()
{
    int cursorPos = getCursorPosition() + static_cast<int>(strlen(INT_TEXT));
    this->rawText.insert(getCursorPosition(), INT_TEXT);
    updateStyledText();

    setCursorPosition(cursorPos);
}

void ExpressionDialog::on_StrButton_released()
{
    int cursorPos = getCursorPosition() + static_cast<int>(strlen(STR_TEXT));
    this->rawText.insert(getCursorPosition(), STR_TEXT);
    updateStyledText();

    setCursorPosition(cursorPos);
}

void ExpressionDialog::on_AgiButton_released()
{
    int cursorPos = getCursorPosition() + static_cast<int>(strlen(AGI_TEXT));
    this->rawText.insert(getCursorPosition(), AGI_TEXT);
    updateStyledText();

    setCursorPosition(cursorPos);
}

void ExpressionDialog::on_ConButton_released()
{
    int cursorPos = getCursorPosition() + static_cast<int>(strlen(CON_TEXT));
    this->rawText.insert(getCursorPosition(), CON_TEXT);
    updateStyledText();

    setCursorPosition(cursorPos);
}

void ExpressionDialog::on_SpiButton_released()
{
    int cursorPos = getCursorPosition() + static_cast<int>(strlen(SPI_TEXT));
    this->rawText.insert(getCursorPosition(), SPI_TEXT);
    updateStyledText();

    setCursorPosition(cursorPos);
}

void ExpressionDialog::on_HpButton_released()
{
    int cursorPos = getCursorPosition() + static_cast<int>(strlen(HP_TEXT));
    this->rawText.insert(getCursorPosition(), HP_TEXT);
    updateStyledText();

    setCursorPosition(cursorPos);
}

void ExpressionDialog::on_MpButton_released()
{
    int cursorPos = getCursorPosition() + static_cast<int>(strlen(MP_TEXT));
    this->rawText.insert(getCursorPosition(), MP_TEXT);
    updateStyledText();

    setCursorPosition(cursorPos);
}

void ExpressionDialog::on_UnitLvlButton_released()
{
    int cursorPos = getCursorPosition() + static_cast<int>(strlen(ULVL_TEXT));
    this->rawText.insert(getCursorPosition(), ULVL_TEXT);
    updateStyledText();

    setCursorPosition(cursorPos);
}

void ExpressionDialog::on_AbilityLvlButton_released()
{
    int cursorPos = getCursorPosition() + static_cast<int>(strlen(ALVL_TEXT));
    this->rawText.insert(getCursorPosition(), ALVL_TEXT);
    updateStyledText();

    setCursorPosition(cursorPos);
}

void ExpressionDialog::on_CheckResourceButton_released()
{
    /*
     * TODO
     * text needs to be checked for syntax errors before string is processed
     */
    Expression *exp = Expression::stringToExpression(rawText);

    Attributes attr = {1,1,1,1,1,1,1,1,1};
    qDebug() << exp->eval(attr);

    if(exp){
        qDebug() << "Good";
    }
    else{
        qDebug() << "Bad";
    }
}
