#include "windowproc.h"

using namespace std;

BOOL EnumWindowsProc(
    HWND hWnd,                  // handle to parent window
    LPARAM lParam               // application-defined value
   );

QStringList listWindowsInfo;   // список с информацией об окнах

windowProc::windowProc(QObject *parent) : QObject(parent)
{

}

void windowProc::runCount()
{
    EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)this);
}

void windowProc::stopCount()
{
    emit lstWindowsInfoSignal(listWindowsInfo);
    listWindowsInfo.clear();
}


BOOL EnumWindowsProc(HWND hWnd, LPARAM lp)
{
    if (IsWindowVisible(hWnd))
    {
        wchar_t Buff[255], NameOfClass[255];
        GetWindowText(hWnd, Buff, 254);
        if (QString::fromWCharArray(Buff) != "")
        {
            QStringList strInfo;
            strInfo.append(QString::fromWCharArray(Buff));
            GetClassName(hWnd, NameOfClass, 254);
            strInfo.append(QString::fromWCharArray(NameOfClass));
            if (hWnd == GetForegroundWindow())
                strInfo.append("True");
            else
                strInfo.append("False");
            listWindowsInfo.append(strInfo);
        }
    }
    return true;
}

