#include "windowproc.h"


using namespace std;

BOOL EnumWindowsProc(
    HWND hWnd,                  // handle to parent window
    LPARAM lParam               // application-defined value
   );


windowProc::windowProc(QObject *parent) : QObject(parent)
{

}

void windowProc::runCount()
{
    EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)this);
}



BOOL EnumWindowsProc(HWND hWnd, LPARAM lp)
{
    if (IsWindowVisible(hWnd))
    {
        wchar_t Buff[255], NameOfClass[255];
        GetWindowText(hWnd, Buff, 254);
        GetClassName(hWnd, NameOfClass, 254);
        qDebug() << QString::fromWCharArray(Buff) << "     " << QString::fromWCharArray(NameOfClass);
    }

   /* if (IsWindowVisible(hWnd))
    {
        WCHAR str[255];
        DWORD procId = NULL;
        GetWindowText(hWnd,str,100);
        GetWindowThreadProcessId(hWnd, &procId);
        qDebug() << QString::fromWCharArray(str);
        //cout << str << endl;
        //cout << "Process -> " << procId << endl;
        //MessageBox(hWnd,(LPCWSTR)str,(LPCWSTR)"123",MB_ICONINFORMATION);
    }*/
    return true;
}

