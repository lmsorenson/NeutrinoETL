#include "neutrinoevent.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

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

NeutrinoTrack * NeutrinoEvent::last()
{
    if (!tracks_.isEmpty())
        return tracks_.last();

    return nullptr;
}

QJsonObject NeutrinoEvent::to_json()
{
    QJsonObject object;
    object.insert("Id", QJsonValue::fromVariant(this->id_));

    QJsonArray tracks;
    for(int i = 0; i < tracks_.size(); ++i)
    {
        tracks.append(tracks_[i]->to_json());
    }

    object.insert("Tracks", tracks);

    return object;
}

void NeutrinoEvent::print()
{
    if (tracks_.isEmpty()) return;

    qDebug() << "******** Event ********";
    for(int i = 0; i < tracks_.size(); ++i)
    {
        tracks_[i]->print();
    }
}

QList<NeutrinoTrack *> NeutrinoEvent::get_tracks() const
{
    return tracks_;
}

float NeutrinoEvent::get_max_charge()
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
