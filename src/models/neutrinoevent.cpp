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

float NeutrinoEvent::get_max_charge() const
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
    object.insert("TotalCharge", 0);
    object.insert("EventDensity", 0);

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
