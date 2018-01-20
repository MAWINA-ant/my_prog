#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>

#include "windowproc.h"
#include "mouse.h"
#include "keyboard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QThread *windowProcThread;              // поток в котором фиксируются все открытые окна Windows
    windowProc *windowProcElement;          // элемент класса обработки окон

    QThread *mouseThread;                   // поток в котором отлавливается передвижение мыши
    mouse *mouseElement;                    // элемент класса мыши

    QThread *keyboardThread;                // поток в котором отлавливается нажатие на кнопку клавиатуры
    keyboard *keyboardElement;              // элемент класса клавиатуры

    QTimer *timerSession;                   // таймер для запуска новой сессии

private slots:
    void timerSessionSlot();

signals:
    void startSession();

};

#endif // MAINWINDOW_H
