#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>

class keyboard : public QObject
{
    Q_OBJECT
public:
    explicit keyboard(QObject *parent = 0);

private:
    long long countKeyPressed;

public:
    int getCountKeyPressed() {return countKeyPressed;}
    void resetCountKeyPressed() {countKeyPressed = 0;}
    bool work;

signals:
    void keyPressed();                      // если была нажата клавиша

public slots:
    void runCount();                        // запуск обработчика нажатия
};

#endif // KEYBOARD_H
