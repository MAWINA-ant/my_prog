#include "keyboard.h"
#include "windows.h"
#include <QDebug>

keyboard::keyboard(QObject *parent) : QObject(parent), countKeyPressed(0)
{
}

void keyboard::runCount()
{
    workFlag = true;
    int keyNumber;
    while(workFlag){
        for (keyNumber = 1; keyNumber <= 254; keyNumber++)
        {
            if (GetAsyncKeyState(keyNumber)==-32767)
                countKeyPressed++;
        }
    }
}

void keyboard::stopCount()
{
    workFlag = false;
    resetCountKeyPressed();
}


