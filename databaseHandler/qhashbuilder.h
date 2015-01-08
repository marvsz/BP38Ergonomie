#ifndef QHASHBUILDER_H
#define QHASHBUILDER_H

#include <QHash>
#include <QStringList>
#include <QList>

template <class T, class U>
class QHashBuilder
{
public:
    QHashBuilder(){

    }

    QHashBuilder(const QStringList &listKey, const QList<QVariant::Type> &listValue){
        for(int i = 0; i < listKey.count(); ++i)
            hash.insert(listKey.at(i), listValue.at(i));
    }

    QHashBuilder& add(const T &key, const U &value){
        hash.insert(key, value);
        return *this;
    }

    QHash<T, U> build(){
        return hash;
    }

private:
    QHash<T, U> hash;
};

#endif // QHASHBUILDER_H
