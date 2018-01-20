#ifndef MOUSE_H
#define MOUSE_H

#include <QObject>
#include <QCursor>
#include <QDebug>


class mouse : public QObject
{
    Q_OBJECT
public:
    explicit mouse(QObject *parent = 0);

private:
    QCursor *cursor;

signals:

public slots:
    void runCount();
};

#endif // MOUSE_H
