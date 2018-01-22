#include "mouse.h"

mouse::mouse(QObject *parent) : QObject(parent), mouseDistance(0)
{
    cursor = new QCursor();
    currentPosition = cursor->pos();
}

void mouse::runCount()
{
    resetMouseDistance();
    workFlag = true;
    while (workFlag)
    {
        if (currentPosition != cursor->pos())
        {
            mouseDistance += sqrt(pow((cursor->pos().x() - currentPosition.x()), 2) + pow((cursor->pos().y() - currentPosition.y()), 2));
            currentPosition = cursor->pos();
        }
    }
}

void mouse::stopCount()
{
    workFlag = false;
}


