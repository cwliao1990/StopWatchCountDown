#ifndef TEST_H
#define TEST_H
#include <QString>
#include <QMetaType>
class Test
{
public:
    Test();
    int num;
    QString name;
//    Test& operator=(const Test& source)
//    {
//        num = source.num;
//        name = source.name;
//        return *this;
//    }
    friend QDataStream& operator<<(QDataStream &ds, const Test &t);
    friend QDataStream& operator>>(QDataStream &ds, Test &t);
};
Q_DECLARE_METATYPE(Test);
#endif // TEST_H
