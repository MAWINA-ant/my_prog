#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "windows.h"
#include <iostream>

using namespace std;

//BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam);

BOOL CALLBACK EnumWindowsProc(
    HWND hwnd,  // handle to parent window
    LPARAM lParam   // application-defined value
   );


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    EnumWindows((WNDENUMPROC)EnumWindowsProc,(LPARAM)NULL);
        //Sleep(1000);

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lp)
{
    if (IsWindowVisible(hwnd))
    {
        char str[255];
        DWORD procId = NULL;
        GetWindowText(hwnd,(LPWSTR)str,100);
        GetWindowThreadProcessId(hwnd, &procId);
        cout << str << endl;
        cout << "Process -> " << procId << endl;
        MessageBox(hwnd,(LPCWSTR)str,(LPCWSTR)"123",MB_ICONINFORMATION);
    }
    return true;
}


