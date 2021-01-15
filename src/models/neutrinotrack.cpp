#include "neutrinotrack.h"
#include "helpers.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

NeutrinoTrack::NeutrinoTrack(int id)
: id_(id)
, points_(QList<NeutrinoPoint *>())
, x_axis_extremes_()
, y_axis_extremes_()
, z_axis_extremes_()
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

void NeutrinoTrack::add_point(NeutrinoPoint *point)
{
    points_ << point;
}

QList<NeutrinoPoint*> NeutrinoTrack::get_points() const
{
    return points_;
}

QPair<NeutrinoPoint*, NeutrinoPoint*> NeutrinoTrack::x_extremes() const { return x_axis_extremes_; }
QPair<NeutrinoPoint*, NeutrinoPoint*> NeutrinoTrack::y_extremes() const { return y_axis_extremes_; }
QPair<NeutrinoPoint*, NeutrinoPoint*> NeutrinoTrack::z_extremes() const { return z_axis_extremes_; }

QVector3D NeutrinoTrack::track_center() const
{
    auto x_coordinate = calculate_axis_center(x_axis_extremes_.first, x_axis_extremes_.second, &NeutrinoPoint::x);
    auto y_coordinate = calculate_axis_center(y_axis_extremes_.first, y_axis_extremes_.second, &NeutrinoPoint::y);
    auto z_coordinate = calculate_axis_center(z_axis_extremes_.first, z_axis_extremes_.second, &NeutrinoPoint::z);

    return QVector3D(x_coordinate, y_coordinate, z_coordinate);
}

double NeutrinoTrack::get_max_charge() const
{
    double max_charge = 0;

    for (int i=0; i < points_.size(); ++i)
    {
        double point_charge = points_[i]->charge();
        if (point_charge > max_charge)
            max_charge = point_charge;
    }

    return max_charge;
}

double NeutrinoTrack::total_charge() const
{
    double total_charge = 0;

    for(auto point : points_)
        total_charge = total_charge + point->charge();

    return total_charge;
}

double NeutrinoTrack::track_density() const
{
    // subtract the max from the min on each axis to get the dimensions.
    double x_dimension = x_axis_extremes_.second->x() - x_axis_extremes_.first->x();
    double y_dimension = y_axis_extremes_.second->y() - y_axis_extremes_.first->y();
    double z_dimension = z_axis_extremes_.second->z() - z_axis_extremes_.first->z();

    double track_volume = x_dimension * y_dimension * z_dimension;

    // if track_volume is 0 track density is undefined.
    if (track_volume == 0) return -999.;

    double track_density = total_charge() / track_volume;

    return track_density;
}

void NeutrinoTrack::calculate_extremes()
{
    QPair<NeutrinoPoint*, NeutrinoPoint*> x, y, z;

    for (int i=0; i < points_.size(); ++i)
    {
        if (is_upper_extreme(points_[i], &NeutrinoPoint::x, x.second)) x.second = points_[i];
        if (is_lower_extreme(points_[i], &NeutrinoPoint::x, x.first)) x.first = points_[i];

        if (is_upper_extreme(points_[i], &NeutrinoPoint::y, y.second)) y.second = points_[i];
        if (is_lower_extreme(points_[i], &NeutrinoPoint::y, y.first)) y.first = points_[i];

        if (is_upper_extreme(points_[i], &NeutrinoPoint::z, z.second)) z.second = points_[i];
        if (is_lower_extreme(points_[i], &NeutrinoPoint::z, z.first)) z.first = points_[i];
    }

    x_axis_extremes_ = x;
    y_axis_extremes_ = y;
    z_axis_extremes_ = z;
}

int32_t NeutrinoTrack::id() const { return id_; }

QJsonObject NeutrinoTrack::to_json() const
{
    QJsonObject object;
    object.insert("Id", QJsonValue::fromVariant(this->id_));

    QJsonArray points;
    for(int i = 0; i < points_.size(); ++i)
    {
        points.append(points_[i]->to_json());
    }

    object.insert("Points", points);

    QJsonObject meta;
    meta.insert("XAxisMinimum", x_axis_extremes_.first->x());
    meta.insert("XAxisMaximum", x_axis_extremes_.second->x());
    meta.insert("YAxisMinimum", y_axis_extremes_.first->y());
    meta.insert("YAxisMaximum", y_axis_extremes_.second->y());
    meta.insert("ZAxisMinimum", z_axis_extremes_.first->z());
    meta.insert("ZAxisMaximum", z_axis_extremes_.second->z());
    meta.insert("TotalCharge", this->total_charge());
    meta.insert("TrackDensity", this->track_density());

    object.insert("Metadata", meta);

    return object;
}

void NeutrinoTrack::print() const
{
    qDebug() << "-------- Track: --------";
    for(int i = 0; i < points_.size(); ++i)
    {
        points_[i]->print();
    }
}