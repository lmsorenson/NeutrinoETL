#include "neutrinopoint.h"

#include <QDebug>
#include <QJsonObject>

NeutrinoPoint::NeutrinoPoint(QMap<QString, float> point_map)
    : id_(point_map["Point no"])
    , x_(point_map["TX"])
    , y_(point_map["TY"])
    , z_(point_map["TZ"])
    , charge_(point_map["charge"])
    , max_charge_(0)
{
}

void NeutrinoPoint::print()
{
    qDebug() << "Point " << id_ << ": " << x_ << ", " << y_ << ", " << z_ << ", charge: " << charge_;
}

QJsonObject NeutrinoPoint::to_json()
{
    if (charge_ > max_charge_)
        max_charge_ = charge_;

    QJsonObject object;
    object.insert("Id", QJsonValue::fromVariant(id_));
    object.insert("X", QJsonValue::fromVariant(x_));
    object.insert("Y", QJsonValue::fromVariant(y_));
    object.insert("Z", QJsonValue::fromVariant(z_));
    object.insert("Charge", QJsonValue::fromVariant(charge_));
    return object;
}

float NeutrinoPoint::get_max_charge()
{
    return max_charge_;
}
