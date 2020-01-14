#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QObject>

class Expression : public QObject
{
    Q_OBJECT
public:
    explicit Expression(QObject *parent = nullptr);

signals:

public slots:
};

#endif // EXPRESSION_H
