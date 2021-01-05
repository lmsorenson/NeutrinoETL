#include "neutrinoevent.h"
#include "helpers.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

NeutrinoEvent::NeutrinoEvent(int id, QObject *parent)
    : QObject(parent)
    , id_(id)
{
}

NeutrinoEvent::~NeutrinoEvent()
{
    for(int i = 0; i < tracks_.size(); ++i)
    {
        delete tracks_[i];
    }

    tracks_.clear();
}

void NeutrinoEvent::add_track(NeutrinoTrack *track)
{
    tracks_.append(track);
}

void NeutrinoEvent::calculate_extremes()
{
    QPair<NeutrinoPoint*, NeutrinoPoint*> x, y, z;

    for (int i=0; i < tracks_.size(); ++i)
    {
        tracks_[i]->calculate_extremes();

        if (is_upper_extreme(tracks_[i]->x_extremes().second, &NeutrinoPoint::x, x.second)) x.second = tracks_[i]->x_extremes().second;
        if (is_lower_extreme(tracks_[i]->x_extremes().first, &NeutrinoPoint::x, x.first)) x.first = tracks_[i]->x_extremes().first;

        if (is_upper_extreme(tracks_[i]->y_extremes().second, &NeutrinoPoint::y, y.second)) y.second = tracks_[i]->y_extremes().second;
        if (is_lower_extreme(tracks_[i]->y_extremes().first, &NeutrinoPoint::y, y.first)) y.first = tracks_[i]->y_extremes().first;

        if (is_upper_extreme(tracks_[i]->z_extremes().second, &NeutrinoPoint::z, z.second)) z.second = tracks_[i]->z_extremes().second;
        if (is_lower_extreme(tracks_[i]->z_extremes().first, &NeutrinoPoint::z, z.first)) z.first = tracks_[i]->z_extremes().first;
    }

    x_axis_extremes_ = x;
    y_axis_extremes_ = y;
    z_axis_extremes_ = z;
}

NeutrinoTrack * NeutrinoEvent::last() const
{
    if (!tracks_.isEmpty())
        return tracks_.last();

    return nullptr;
}

QList<NeutrinoTrack *> NeutrinoEvent::get_tracks() const
{
    return tracks_;
}

QPair<NeutrinoPoint*, NeutrinoPoint*> NeutrinoEvent::x_extremes() const { return x_axis_extremes_; }
QPair<NeutrinoPoint*, NeutrinoPoint*> NeutrinoEvent::y_extremes() const { return y_axis_extremes_; }
QPair<NeutrinoPoint*, NeutrinoPoint*> NeutrinoEvent::z_extremes() const { return z_axis_extremes_; }



QVector3D NeutrinoEvent::event_center() const
{
    auto x_coordinate = calculate_axis_center(x_axis_extremes_.first, x_axis_extremes_.second, &NeutrinoPoint::x);
    auto y_coordinate = calculate_axis_center(y_axis_extremes_.first, y_axis_extremes_.second, &NeutrinoPoint::y);
    auto z_coordinate = calculate_axis_center(z_axis_extremes_.first, z_axis_extremes_.second, &NeutrinoPoint::z);

    return QVector3D(x_coordinate, y_coordinate, z_coordinate);
}

double NeutrinoEvent::get_max_charge() const
{
    float max_charge = 0;

    for (int i=0; i < tracks_.size(); ++i)
    {
        float max_track_charge = tracks_[i]->get_max_charge();
        if (max_track_charge > max_charge)
            max_charge = max_track_charge;
    }

    return max_charge;
}

double NeutrinoEvent::total_charge() const
{
    double total_charge = 0;

    for(auto point : tracks_)
        total_charge = total_charge + point->total_charge();

    return total_charge;
}

double NeutrinoEvent::track_density() const
{
    double x_dimension = x_axis_extremes_.second->x() - x_axis_extremes_.first->x();
    double y_dimension = y_axis_extremes_.second->y() - y_axis_extremes_.first->y();
    double z_dimension = z_axis_extremes_.second->z() - z_axis_extremes_.first->z();

    double track_volume = x_dimension * y_dimension * z_dimension;

    double track_density = total_charge() / track_volume;

    return track_density;
}

QJsonObject NeutrinoEvent::to_json() const
{
    QJsonObject object;
    object.insert("Id", QJsonValue::fromVariant(this->id_));

    QJsonArray tracks;
    for(int i = 0; i < tracks_.size(); ++i)
    {
        tracks.append(tracks_[i]->to_json());
    }

    object.insert("Tracks", tracks);

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

void NeutrinoEvent::print() const
{
    if (tracks_.isEmpty()) return;

    qDebug() << "******** Event ********";
    for(int i = 0; i < tracks_.size(); ++i)
    {
        tracks_[i]->print();
    }
}
