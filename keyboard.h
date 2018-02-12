#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
#include <QList>

class keyboard : public QObject
{
    Q_OBJECT
public:
    explicit keyboard(QObject *parent = 0);

    long long getCountKeyPressed() {return countKeyPressed;}
    void resetCountKeyPressed() {countKeyPressed = 0;}

private:
    long long countKeyPressed;
    bool workFlag;
    QList<int> lstPressedKey;

signals:
    void keyPressed();                      // если была нажата клавиша

public slots:
    void runCount();                        // запуск обработчика нажатия
    void stopCount();                       // остановка подсчета
};

#endif // KEYBOARD_H
