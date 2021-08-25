#include "test.h"

Test::Test()
{

}
QDataStream& operator<<(QDataStream &ds, const Test &t)
{
    QString num;
    num = QString("%1").arg(t.num, 1, 10, QChar('0'));
    ds << num << t.name;
    return ds;
}

QDataStream& operator>>(QDataStream &ds, Test &t)
{

    QString num;
    QString name;

    ds >> num >> name;

    t.num = num.toInt();
    t.name = name;
    return ds;
}
