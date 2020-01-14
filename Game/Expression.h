#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QObject>
#include <QString>
#include <QStack>
#include "Globals.h"

class Expression : public QObject
{
    Q_OBJECT
public:
    enum OperationType{
        ADD,
        SUB,
        MUL,
        DIV,
        N_OPERATORS
    };

    enum ExpressionType{
        DOUBLE,
        ATTRIBUTE,
        EXPRESSION,
        N_EXPRESSION_TYPES
    };

    Expression(double val);
    Expression(AttributeType attribute);
    Expression(Expression* left, Expression* right, OperationType operation);

    double eval(Attributes attr);

    static Expression* stringToExpression(QString str);
    static int operatorPrecedence(QString str);
    static QString getNextOperand(QString str);
    static QString getNextAttribute(QString str);
    static QStack<QString> toPostFix(QString str);
    static int getNextOperatorIdx(QStack<QString> postfix);
    static OperationType stringToOperationType(QString str);
    static Expression* stringOperandToExpression(QString str);
    static void getNextExpressionFromStack(QStack<QString> &postfix, QStack<Expression*> &expressions, int nextOpIdx);
    static bool checkIfExpressionStringIsValid(QString str);

    QString toString();
    QString operatorToString();

    QString dump();
signals:

public slots:

private:
    Expression* left    = nullptr;
    Expression* right   = nullptr;
    OperationType op    = ADD;
    double dVal         = 0;
    AttributeType attr  = STR;
    ExpressionType type = DOUBLE;

    double getAttr(Attributes attr);
    double operate(double lval, double rval);
};

#endif // EXPRESSION_H
