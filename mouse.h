#ifndef MOUSE_H
#define MOUSE_H

#include <QObject>
#include <QCursor>
#include <QDebug>
#include <math.h>


class mouse : public QObject
{
    Q_OBJECT
public:
    explicit mouse(QObject *parent = 0);

    long long getMouseDistance() {return mouseDistance;}
    void resetMouseDistance() {mouseDistance = 0;}

private:
    QCursor *cursor;
    bool workFlag;
    long long mouseDistance;
    QPoint currentPosition;

signals:

public slots:
    void runCount();
    void stopCount();                       // остановка подсчета
};

#endif // MOUSE_H
