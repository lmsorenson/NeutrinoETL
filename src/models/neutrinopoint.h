#pragma once

#include <QObject>
#include <QMap>

class NeutrinoPoint : QObject
{
    Q_OBJECT
public:
    NeutrinoPoint(QMap<QString, float> point_map);
    virtual ~NeutrinoPoint() = default;

    QJsonObject to_json();
    void print();

private:
    float id_, x_, y_, z_, charge_;
};

