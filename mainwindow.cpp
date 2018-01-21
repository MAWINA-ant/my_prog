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

    connect(this, SIGNAL(stopSession()), this, SLOT(stopSessionSlot()));

    //***********************************************************************************
    // для клавиатуры
    //***********************************************************************************

    keyboardThread = new QThread();
    connect(this, SIGNAL(destroyed(QObject*)), keyboardThread, SLOT(quit()));
    connect(this, SIGNAL(destroyed(QObject*)), keyboardThread, SLOT(deleteLater()));
    keyboardElement = new keyboard();
    connect(this, SIGNAL(startSession()), keyboardElement, SLOT(runCount()));
    keyboardElement->moveToThread(keyboardThread);
    keyboardThread->start();

    //***********************************************************************************
    // для мыши
    //***********************************************************************************

    mouseThread = new QThread(this);
    connect(this, SIGNAL(destroyed(QObject*)), mouseThread, SLOT(quit()));
    connect(this, SIGNAL(destroyed(QObject*)), mouseThread, SLOT(deleteLater()));
    mouseElement = new mouse();
    connect(this, SIGNAL(startSession()), mouseElement, SLOT(runCount()));
    mouseElement->moveToThread(mouseThread);
    mouseThread->start();

    //***********************************************************************************
    // для окон приложений
    //***********************************************************************************

    windowProcThread = new QThread(this);
    connect(this, SIGNAL(destroyed(QObject*)), windowProcThread, SLOT(quit()));
    connect(this, SIGNAL(destroyed(QObject*)), windowProcThread, SLOT(deleteLater()));
    windowProcElement = new windowProc();
    connect(this, SIGNAL(startSession()), windowProcElement, SLOT(runCount()));
    windowProcElement->moveToThread(windowProcThread);
    windowProcThread->start();

    //***********************************************************************************
    // таймер новой сессии
    //***********************************************************************************

    timerSession = new QTimer(this);
    connect(timerSession, SIGNAL(timeout()), this, SLOT(timerSessionSlot()));
    timerSession->start(5000);

    emit startSession();
}

MainWindow::~MainWindow()
{
    emit stopSession();
    keyboardThread->exit(0);
    keyboardThread->wait();
    mouseThread->exit(0);
    mouseThread->wait();
    windowProcThread->exit(0);
    windowProcThread->wait();

    delete ui;
}

void MainWindow::timerSessionSlot()
{
    ui->lineEditKeyPressedCount->setText(QString::number(keyboardElement->getCountKeyPressed()));
    ui->lineEditRangeMouse->setText(QString::number(mouseElement->getMouseDistance()));
    emit stopSession();
    emit startSession();
}

void MainWindow::stopSessionSlot()
{
    keyboardElement->stopCount();
    mouseElement->stopCount();
    windowProcElement->stopCount();
}



