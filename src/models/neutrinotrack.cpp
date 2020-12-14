#include "neutrinotrack.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

NeutrinoTrack::NeutrinoTrack(int id) : id_(id), points_(QList<NeutrinoPoint *>())
{

}

NeutrinoTrack::~NeutrinoTrack()
{
    for(int i = 0; i < points_.size(); ++i)
    {
        delete points_[i];
    }

    points_.clear();
}

QJsonObject NeutrinoTrack::to_json()
{
    QJsonObject object;
    object.insert("Id", QJsonValue::fromVariant(this->id_));

    QJsonArray points;
    for(int i = 0; i < points_.size(); ++i)
    {
        points.append(points_[i]->to_json());
    }

    object.insert("Points", points);

    return object;
}

void NeutrinoTrack::add_point(NeutrinoPoint *point)
{
    points_.append(point);
}

void NeutrinoTrack::print()
{
    qDebug() << "-------- Track: --------";
    for(int i = 0; i < points_.size(); ++i)
    {
        points_[i]->print();
    }
}

float NeutrinoTrack::get_max_charge()
{
    float max_charge = 0;
    for (int i=0; i < points_.size(); ++i)
    {
        float point_charge = points_[i]->get_max_charge();
        if (point_charge > max_charge)
            max_charge = point_charge;
    }

    return max_charge;
}
