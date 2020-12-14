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

    float get_max_charge();

private:
    float id_, x_, y_, z_, charge_, max_charge_;
};

