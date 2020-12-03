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

private:
    int id_;
    QList<NeutrinoTrack *> tracks_;

signals:

};
