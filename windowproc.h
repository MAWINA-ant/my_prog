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

private:

signals:
    void lstWindowsInfoSignal(QStringList);

public slots:
    void runCount();                        // запуск посчета открытых окон
    void stopCount();                       // остановка подсчета

};

#endif // WINDOWPROC_H
