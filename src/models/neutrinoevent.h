#pragma once

#include <QObject>
#include <src/models/neutrinotrack.h>

class NeutrinoEvent : public QObject
{
    Q_OBJECT
public:
    explicit NeutrinoEvent(int id, QObject *parent = nullptr);
    virtual ~NeutrinoEvent();

    void add_track(NeutrinoTrack *track);
    NeutrinoTrack * last();
    QJsonObject to_json();
    void print();

    QList<NeutrinoTrack *> get_tracks() const;
    float get_max_charge();

private:
    int id_;
    QList<NeutrinoTrack *> tracks_;

signals:

};
