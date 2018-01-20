#include "mouse.h"

mouse::mouse(QObject *parent) : QObject(parent)
{
    cursor = new QCursor();

}

void mouse::runCount()
{
    while (1)
    {
        //qDebug() << cursor->pos();
    }
}


