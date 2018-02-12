#include "keyboard.h"
#include "windows.h"
#include <QDebug>

keyboard::keyboard(QObject *parent) : QObject(parent), countKeyPressed(0)
{
}

void keyboard::runCount()
{
    resetCountKeyPressed();
    workFlag = true;
    int keyNumber;
    while(workFlag){
        for (keyNumber = 8; keyNumber <= 254; keyNumber++)
        {
            if (keyNumber == 16 || keyNumber == 17 || keyNumber == 18)
                continue;
            if (GetAsyncKeyState(keyNumber) == -32767)
                countKeyPressed++;
        }
    }
}

void keyboard::stopCount()
{
    workFlag = false;
}


