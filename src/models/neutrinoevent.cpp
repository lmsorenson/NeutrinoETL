#include "neutrinoevent.h"

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
    for (int i=0; i < tracks_.size(); ++i)
    {
        tracks_[i]->calculate_extremes();
    }
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
