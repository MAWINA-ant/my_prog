#include "keyboard.h"
#include "windows.h"
#include <QDebug>

keyboard::keyboard(QObject *parent) : QObject(parent)
{
    work = true;
}

void keyboard::runCount()
{
    int keyNumber;
    while(work){
        for (keyNumber = 1; keyNumber <= 254; keyNumber++)
        {
            if (GetAsyncKeyState(keyNumber)==-32767)
                countKeyPressed++;
        }
    }
}


