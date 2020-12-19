#pragma once

#include <QObject>
#include <QMap>

class NeutrinoPoint : QObject
{
    Q_OBJECT
public:
    NeutrinoPoint(QMap<QString, double> point_map);
    virtual ~NeutrinoPoint() = default;

    double x() const;
    double y() const;
    double z() const;
    double charge() const;

    QJsonObject to_json() const;
    void print() const;
private:
    double id_, x_, y_, z_, charge_;
};

