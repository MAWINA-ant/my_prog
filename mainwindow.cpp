#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "windows.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //***********************************************************************************
    // для клавиатуры
    //***********************************************************************************

    keyboardThread = new QThread(this);
    connect(this, SIGNAL(destroyed(QObject*)), keyboardThread, SLOT(quit()));
    connect(this, SIGNAL(destroyed(QObject*)), keyboardThread, SLOT(deleteLater()));
    keyboardElement = new keyboard();
    keyboardElement->resetCountKeyPressed();
    connect(this, SIGNAL(startSession()), keyboardElement, SLOT(runCount()));
    keyboardElement->moveToThread(keyboardThread);
    keyboardThread->start();

    //***********************************************************************************
    // для мыши
    //***********************************************************************************

    mouseThread = new QThread(this);
    connect(this, SIGNAL(destroyed(QObject*)), mouseThread, SLOT(quit()));
    mouseElement = new mouse();
    //connect(this, SIGNAL(startSession()), mouseElement, SLOT(runCount()));
    mouseElement->moveToThread(mouseThread);
    mouseThread->start();

    //***********************************************************************************
    // для окон приложений
    //***********************************************************************************

    windowProcThread = new QThread(this);
    connect(this, SIGNAL(destroyed(QObject*)), windowProcThread, SLOT(quit()));
    windowProcElement = new windowProc();
    connect(this, SIGNAL(startSession()), windowProcElement, SLOT(runCount()));
    windowProcElement->moveToThread(windowProcThread);
    windowProcThread->start();

    //***********************************************************************************
    // таймер новой сессии
    //***********************************************************************************

    timerSession = new QTimer(this);
    connect(timerSession, SIGNAL(timeout()), this, SLOT(timerSessionSlot()));
    //timerSession->start(10000);

    emit startSession();
}

MainWindow::~MainWindow()
{
    keyboardElement->work = false;
    keyboardThread->exit(0);
    keyboardThread->deleteLater();
    keyboardThread->wait(2000);
    /*mouseThread->quit();
    mouseThread->wait();
    windowProcThread->quit();
    windowProcThread->wait();*/
    delete ui;
}

void MainWindow::timerSessionSlot()
{
    ui->lineEditKeyPressedCount->setText(QString::number(keyboardElement->getCountKeyPressed()));
    keyboardElement->resetCountKeyPressed();
}



