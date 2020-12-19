#include "neutrinopoint.h"

#include <QDebug>
#include <QJsonObject>

NeutrinoPoint::NeutrinoPoint(QMap<QString, double> point_map)
    : id_(-1), x_(-1), y_(-1), z_(-1), charge_(-1)
{
    id_ = point_map["Point no"];
    x_ = point_map["TX"];
    y_ = point_map["TY"];
    z_ = point_map["TZ"];
    charge_ = point_map["charge"];

}

void NeutrinoPoint::print()
{
    qDebug() << "Point " << id_ << ": " << x_ << ", " << y_ << ", " << z_ << ", charge: " << charge_;
}

QJsonObject NeutrinoPoint::to_json()
{
    QJsonObject object;
    object.insert("Id", QJsonValue(id_));
    object.insert("X", QJsonValue(x_));
    object.insert("Y", QJsonValue(y_));
    object.insert("Z", QJsonValue(z_));
    object.insert("Charge", QJsonValue(charge_));

    return object;
}

double NeutrinoPoint::x() const { return x_; }
double NeutrinoPoint::y() const { return y_; }
double NeutrinoPoint::z() const { return z_; }
double NeutrinoPoint::charge() const { return z_; }
