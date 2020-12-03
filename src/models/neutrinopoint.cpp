#include "neutrinopoint.h"

#include <QDebug>

NeutrinoPoint::NeutrinoPoint(QMap<QString, float> point_map) : id_(point_map["Point no"]), x_(point_map["TX"]), y_(point_map["TY"]), z_(point_map["TZ"]), charge_(point_map["charge"])
{
    qDebug() << "id " << id_ << " X: " << x_ << " Y: " << y_ << " Z: " << " Charge: " << charge_;
}
