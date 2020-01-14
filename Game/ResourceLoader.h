#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <QObject>

class ResourceLoader : public QObject
{
    Q_OBJECT
public:
    explicit ResourceLoader(QObject *parent = nullptr);

    //Game loading functions

    //Level loading functions

    //Object loading functions

signals:

public slots:
};

#endif // RESOURCELOADER_H
