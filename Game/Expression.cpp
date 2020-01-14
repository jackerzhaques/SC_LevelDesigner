#include "Expression.h"

#include <QDebug>

Expression::Expression(double val)
{
    this->dVal = val;
    this->type = DOUBLE;
}

Expression::Expression(AttributeType attribute)
{
    this->attr = attribute;
    this->type = ATTRIBUTE;
}

Expression::Expression(Expression *left, Expression *right, Expression::OperationType operation)
{
    this->left  = left;
    this->right = right;
    this->op    = operation;
    this->type  = EXPRESSION;
}

double Expression::eval(Attributes attr)
{
    double val = 0, lval = 0, rval = 0;

    switch(type){
        case DOUBLE:
            val = dVal;
            break;
        case ATTRIBUTE:
            val = getAttr(attr);
            break;
        case EXPRESSION:
            lval = left->eval(attr);
            rval = right->eval(attr);
            val = operate(lval, rval);
            break;
        default:
            //Invalid case
            break;
    }

    return val;
}

Expression *Expression::stringToExpression(QString str)
{
    Expression *exp = nullptr;
    bool isValid = checkIfExpressionStringIsValid(str);

    if(isValid){
        QStack<Expression*> expressions;

        //Convert the (infix) expression to postfix for easier processing
        QStack<QString> postfix = toPostFix(str);

        /*
         * Convert each postfix expression into a data struct expression and
         * push it to the expression stack.
         *
         * The next postfix expression is always the one right before the next operator
         *
         * Cases:
         *  2 opnds before oper: Create and push new expression
         *  1 opnds before oper: Create expr, left side is last expr in stack, right side is opnd.
         *  0 opnds before oper: Create expr, left side is 2 expr ago, right side is last expr in stack.
         */

        while(postfix.size() > 0){
            int nextOpIdx = getNextOperatorIdx(postfix);

            if(nextOpIdx >= 0){
                getNextExpressionFromStack(postfix, expressions, nextOpIdx);
            }
            else{
                //Not an operator.
                //If we reach this case, just convert the first operand to an expression and return it.
                //This is usually because there is only an operand in the stack
                //Sometimes it is because the expression is malformed, but that should not happen if the string is properly checked
                //The worst case scenario is that a value of 0 is returned
                Expression *e = stringOperandToExpression(postfix[0]);
                expressions.push(e);
                break;  //End the loop in this case.
            }
        }

        if(!expressions.isEmpty()){
            exp = expressions.top();
        }
    }

    return exp;
}

int Expression::operatorPrecedence(QString str)
{
    //PEMDAS
    int val = -1;
    if(str == "-"){
        val = 0;
    }
    else if(str == "+"){
        val = 1;
    }
    else if(str == "/"){
        val = 2;
    }
    else if(str == "*"){
        val = 3;
    }
    else{
        //Invalid case
    }

    return val;
}

QString Expression::getNextOperand(QString str)
{
    QString operand = "";

    for(int i = 0; i < str.length(); i++){
        //If the character is a number, add it the operand.
        //If not, exit the loop
        if((str[i] >= '0' && str[i] <= '9') || str[i] == '.'){
            operand += str[i];
        }
        else{
            break;
        }
    }

    return operand;
}

QString Expression::getNextAttribute(QString str)
{
    QString attribute = "";

    if( str.indexOf(STR_TEXT) == 0){
        attribute = STR_TEXT;
    }
    else if( str.indexOf(INT_TEXT) == 0){
        attribute = INT_TEXT;
    }
    else if( str.indexOf(AGI_TEXT) == 0){
        attribute = AGI_TEXT;
    }
    else if( str.indexOf(CON_TEXT) == 0){
        attribute = CON_TEXT;
    }
    else if( str.indexOf(SPI_TEXT) == 0){
        attribute = SPI_TEXT;
    }
    else if( str.indexOf(HP_TEXT) == 0){
        attribute = HP_TEXT;
    }
    else if( str.indexOf(MP_TEXT) == 0){
        attribute = MP_TEXT;
    }
    else if( str.indexOf(ULVL_TEXT) == 0){
        attribute = ULVL_TEXT;
    }
    else if( str.indexOf(ALVL_TEXT) == 0){
        attribute = ALVL_TEXT;
    }
    else{
        //No attribute text found
    }

    return attribute;
}

QStack<QString> Expression::toPostFix(QString str)
{
    QStack<QString> operators;
    QStack<QString> postfix;

    //Clear whitespace
    str = str.simplified();
    str = str.replace(" ", "");

    //Mark the beginning of operators with B
    operators.push("B");

    while(str.length() > 0){
        QChar c = str[0];

        //qDebug() << getNextOperand(str);
        //qDebug() << getNextAttribute(str);

        QString nextOperand = getNextOperand(str);
        QString nextAttribute = getNextAttribute(str);

        if(!nextOperand.isEmpty()){
            postfix.push(nextOperand);
            str.remove(0, nextOperand.length());
        }
        else if(!nextAttribute.isEmpty()){
            postfix.push(nextAttribute);
            str.remove(0, nextAttribute.length());
        }
        else{
            if(c == '('){
                operators.push(c);
            }
            else if(c == ')'){
                while(operators.top() != 'B' && operators.top() != '('){
                    QString top = operators.top();
                    qDebug() << top;
                    operators.pop();
                    postfix.push(top);
                }

                if(operators.top() == "("){
                    operators.pop();
                }
            }
            else{
                while(operators.top() != "B" &&
                      operatorPrecedence(c) <= operatorPrecedence(operators.top()))
                {
                    QString top = operators.top();
                    operators.pop();
                    postfix.push(top);
                }
                operators.push(c);
            }

            //Remove the character from the string
            str.remove(0, 1);
        }
    }

    while(operators.top() != "B"){
        postfix.push(operators.top());
        operators.pop();
    }

    return postfix;
}

int Expression::getNextOperatorIdx(QStack<QString> postfix)
{
    int idx = -1;

    for(int i = 0; i < postfix.size(); i++){
        QString str = postfix.at(i);
        if(str == "+" ||
            str == "-" ||
            str == "/" ||
            str == "*")
        {
            idx = i;
            break;
        }
    }

    return idx;
}

Expression::OperationType Expression::stringToOperationType(QString str)
{
    OperationType type = ADD;

    if(str == "+"){
        type = ADD;
    }
    else if(str == "-"){
        type = SUB;
    }
    else if(str == "/"){
        type = DIV;
    }
    else if(str == "*"){
        type = MUL;
    }
    else{
        //Invalid type
    }

    return type;
}

Expression *Expression::stringOperandToExpression(QString str)
{
    Expression *exp = nullptr;

    QString val = getNextOperand(str);
    QString attr = getNextAttribute(str);

    if(!val.isEmpty()){
        //Value found
        double dVal = val.toDouble();
        exp = new Expression(dVal);
    }
    else if(!attr.isEmpty()){
        //Attribute found
        AttributeType type = stringToAttributeType(attr);
        exp = new Expression(type);
    }
    else{
        //Invalid input
    }

    return exp;
}

void Expression::getNextExpressionFromStack(QStack<QString> &postfix, QStack<Expression*> &expressions, int nextOpIdx)
{
    QString opText = postfix.at(nextOpIdx);
    OperationType op = stringToOperationType(opText);

    if(nextOpIdx == 0){
        //Only an operator, case 3
        Expression* rexp = expressions.pop();
        Expression* lexp = expressions.pop();
        Expression* exp = new Expression(rexp,lexp,op);
        expressions.push(exp);

        //Remove the operator from the stack
        postfix.removeAt(nextOpIdx);
    }
    else if(nextOpIdx == 1){
        //Only one term before, case 2

        //Convert the operand right before the operator to an expression
        int rexpIdx = nextOpIdx - 1;
        QString rExpStr = postfix[rexpIdx];
        Expression *rexp = stringOperandToExpression(rExpStr);

        //Grab the last expression in the stack as the left expression
        Expression *lexp = expressions.pop();

        //Group both into one expression
        Expression *exp = new Expression(lexp,rexp,op);
        expressions.push(exp);

        //Remove the operand and operator from the stack
        postfix.removeAt(nextOpIdx);
        postfix.removeAt(rexpIdx);
    }
    else if(nextOpIdx >= 2){
        //Two terms before, case 1
        int lexpIdx = nextOpIdx - 2;
        int rexpIdx = nextOpIdx - 1;

        QString lExpStr = postfix[lexpIdx];
        QString rExpStr = postfix[rexpIdx];

        //Convert the operands into expressions
        Expression* lexp = stringOperandToExpression(lExpStr);
        Expression* rexp = stringOperandToExpression(rExpStr);

        //Group both operand expressions into one
        Expression* exp = new Expression(lexp, rexp, op);
        expressions.push(exp);

        //Remove both operands and the operator from the postfix stack
        postfix.removeAt(nextOpIdx);
        postfix.removeAt(rexpIdx);
        postfix.removeAt(lexpIdx);
    }
}

bool Expression::checkIfExpressionStringIsValid(QString str)
{
    bool isValid = true;

    /*
     * String is invalid if it has text that doesn't correspond
     * to an attribute
     */

    return isValid;
}

QString Expression::toString()
{
    QString result;

    switch(type){
        case DOUBLE:
            result = QString::number(dVal);
            break;
        case ATTRIBUTE:
            result = "[" + attributeTypeToString(attr) + "]";
            break;
        case EXPRESSION:
        {
            QString leftSide = left->toString();
            QString rightSide = right->toString();
            QString opText = operatorToString();
            result = leftSide + opText + rightSide;
            break;
        }
        default:
            //Do nothing
            break;
    }

    return result;
}

QString Expression::operatorToString()
{
    QString result;

    switch(op){
        case ADD:
            result = "+";
            break;
        case SUB:
            result = "-";
            break;
        case MUL:
            result = "*";
            break;
        case DIV:
            result = "/";
            break;
        default:
            break;
    }

    return result;
}

QString Expression::dump()
{
    QString retVal = "";

    switch(type){
        case DOUBLE:
            retVal = QString::number(dVal);
            break;
        case ATTRIBUTE:
            retVal = attributeTypeToString(attr);
            break;
        case EXPRESSION:
            retVal = "Expression(" + left->dump() + "," + right->dump() + "," + op + ")";
            break;
        default:
            //Invalid type
            break;
    }

    return retVal;
}

double Expression::getAttr(Attributes attr)
{
    double val = 0;

    switch(this->attr){
        case STR:
            val = attr.str;
            break;
        case INT:
            val = attr.inte;
            break;
        case AGI:
            val = attr.agi;
            break;
        case CON:
            val = attr.con;
            break;
        case SPI:
            val = attr.spi;
            break;
        case HP:
            val = attr.hp;
            break;
        case MP:
            val = attr.mp;
            break;
        case ULVL:
            val = attr.ulvl;
            break;
        case ALVL:
            val = attr.alvl;
            break;
        default:
            //Invalid case
            break;
    }

    return val;
}

double Expression::operate(double lval, double rval)
{
    double val = 0;

    switch(op){
        case ADD:
            val = lval + rval;
            break;
        case SUB:
            val = lval - rval;
            break;
        case MUL:
            val = lval * rval;
            break;
        case DIV:
            val = lval / rval;
            break;
        default:
            //Invalid case
            break;
    }

    return val;
}
