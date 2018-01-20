#ifndef WINDOWPROC_H
#define WINDOWPROC_H

#include <QObject>
#include <QDebug>
#include "windows.h"

class windowProc : public QObject
{
    Q_OBJECT
public:
    explicit windowProc(QObject *parent = 0);

signals:

public slots:
    void runCount();
};

#endif // WINDOWPROC_H
