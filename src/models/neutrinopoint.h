#pragma once

#include <QObject>
#include <QMap>

class NeutrinoPoint : QObject
{
    Q_OBJECT
public:
    NeutrinoPoint(QMap<QString, float> point_map);
    virtual ~NeutrinoPoint() = default;

    float id_, x_, y_, z_, charge_;
};

