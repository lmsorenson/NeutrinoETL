#include "neutrinotrack.h"

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
    double x_dimension = x_axis_extremes_.second->x() - x_axis_extremes_.first->x();
    double y_dimension = y_axis_extremes_.second->y() - y_axis_extremes_.first->y();
    double z_dimension = z_axis_extremes_.second->z() - z_axis_extremes_.first->z();

    double track_volume = x_dimension * y_dimension * z_dimension;

    double track_density = total_charge() / track_volume;

    return track_density;
}

bool is_upper_extreme(NeutrinoPoint* point, double (NeutrinoPoint::*get_axis_value)() const, NeutrinoPoint* axis_max_point)
{
    if (!axis_max_point)
        return true;

    double axis_value = (point->*get_axis_value)();
    double axis_max_value = (axis_max_point->*get_axis_value)();

    return (axis_value > axis_max_value);
}

bool is_lower_extreme(NeutrinoPoint* point, double (NeutrinoPoint::*get_axis_value)() const, NeutrinoPoint* axis_min_point)
{
    if (!axis_min_point)
        return true;

    double axis_value = (point->*get_axis_value)();
    double axis_min_value = (axis_min_point->*get_axis_value)();

    return (axis_value < axis_min_value);
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