#include "windowproc.h"


using namespace std;

BOOL EnumWindowsProc(
    HWND hWnd,                  // handle to parent window
    LPARAM lParam               // application-defined value
   );


windowProc::windowProc(QObject *parent) : QObject(parent)
{
    wchar_t Buff[255], NameOfClass[255];
    HWND hWnd;
    hWnd == GetDesktopWindow();
    GetWindowText(hWnd, Buff, 254);
    GetClassName(hWnd, NameOfClass, 254);
    qDebug() << QString::fromWCharArray(Buff) <<  QString::fromWCharArray(NameOfClass);
}

void windowProc::runCount()
{
    EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)this);
}

void windowProc::stopCount()
{
}



BOOL EnumWindowsProc(HWND hWnd, LPARAM lp)
{
    if (IsWindowVisible(hWnd))
    {
        wchar_t Buff[255], NameOfClass[255];
        GetWindowText(hWnd, Buff, 254);
        if (QString::fromWCharArray(Buff) != "")
        {
            QString strInfo;
            strInfo = QString::fromWCharArray(Buff) + "   ";
            GetClassName(hWnd, NameOfClass, 254);
            strInfo += QString::fromWCharArray(NameOfClass) + "   ";
            if (hWnd == GetActiveWindow())
                strInfo += "Focused";
            else
                strInfo += "Unfocused";
            //qDebug() << strInfo;
        }
    }
    return true;
}

