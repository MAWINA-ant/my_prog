#include "mydatabase.h"
#include <QDebug>

mydatabase::mydatabase(QObject *parent) : QObject(parent)
{
    createDatabase();
}

void mydatabase::createDatabase()
{
    if (!createConnection()) {
        return;
    }
    QSqlQuery query;
    QString table1 = "CREATE TABLE windows("
                  "applicationName TEXT, "
                  "windowTitle TEXT, "
                  "flagActive BOOLEAN, "
                  "idSession INTEGER)";
    if (!query.exec(table1)) {
        qDebug() << "Unable to create a table inventory";
    }
    QString table2 = "CREATE TABLE session("
                   "mouse DOUBLE, "
                   "keyboard DOUBLE, "
                   "idSession INTEGER)";
    if (!query.exec(table2)) {
        qDebug() << "Unable to create a table object";
    }
}

void mydatabase::insertDataInventory(QString strNewType, int newCount, int newCellIndex, int newSize)
{
    QSqlQuery query;
    query.prepare("INSERT INTO inventory (typeObject, count, cellIndex, size)"
                                  "VALUES (:typeObject, :count, :cellIndex, :size);");
    query.bindValue(":typeObject", strNewType);
    query.bindValue(":count", QString::number(newCount));
    query.bindValue(":cellIndex", QString::number(newCellIndex));
    query.bindValue(":size", QString::number(newSize));
        if (!query.exec()) {
            qDebug() << "Unable to insert data in table inventory";
        }
}

void mydatabase::updateDataInventory(int newCount, int CellIndex)
{
    QSqlQuery query;
    query.prepare("UPDATE inventory SET count = :count WHERE cellIndex = :cellIndex");
    query.bindValue(":count", QString::number(newCount));
    query.bindValue(":cellIndex", QString::number(CellIndex));
        if (!query.exec()) {
            qDebug() << "Unable to update data in table inventory";
        }
}

void mydatabase::removeDataInventory(int CellIndex)
{
    QSqlQuery query;
    query.prepare("DELETE FROM inventory  WHERE cellIndex = :cellIndex");
    query.bindValue(":cellIndex", QString::number(CellIndex));
        if (!query.exec()) {
            qDebug() << "Unable to remove data in table inventory";
        }
}

void mydatabase::insertDataObject(QString typeObject, QString typeObjectPath)
{
    QSqlQuery query;
    query.prepare("INSERT INTO object (typeObject, iconPath)"
                                  "VALUES (:typeObject, :iconPath);");
    query.bindValue(":typeObject", typeObject);
    query.bindValue(":iconPath", typeObjectPath);
        if (!query.exec()) {
            qDebug() << "Unable to insert data in table object";
        }
}

void mydatabase::removeDataObject(QString typeObject)
{
    QSqlQuery query;
    query.prepare("DELETE FROM object  WHERE typeObject = :typeObject");
    query.bindValue(":typeObject", typeObject);
        if (!query.exec()) {
            qDebug() << "Unable to remove data in table object";
        }
}

void mydatabase::clearDataBase(int size)
{
    QSqlQuery query;
    query.prepare("DELETE FROM inventory  WHERE size = :size");
    query.bindValue(":size", QString::number(size));
        if (!query.exec()) {
            qDebug() << "Unable to remove data in table inventory";
        }
}

void mydatabase::receivedData()
{
    QSqlQuery query("SELECT a.typeObject, a.count, a.cellIndex, b.iconPath "
                    "FROM inventory as a, object as b WHERE a.typeObject = b.typeObject");
    while (query.next()) {
        QString typeObject = query.value(0).toString();
        int count = query.value(1).toInt();
        int cellIndex = query.value(2).toInt();
        QString iconPath = query.value(3).toString();
        emit sendData(typeObject, count, cellIndex, iconPath);
    }
}

bool mydatabase::createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataBaseSessions");
    db.setUserName ("user");
    db.setHostName ("localhost");
    db.setPassword ("password");
    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    }
    return true;
}

