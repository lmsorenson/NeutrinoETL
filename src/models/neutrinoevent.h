#pragma once

#include <QObject>
#include <models/neutrinotrack.h>

class NeutrinoEvent : public QObject
{
    Q_OBJECT
public:
    explicit NeutrinoEvent(int id, QObject *parent = nullptr);
    virtual ~NeutrinoEvent();

    void add_track(NeutrinoTrack *track);
    void calculate_extremes();

    NeutrinoTrack * last() const;
    QList<NeutrinoTrack *> get_tracks() const;
    QPair<NeutrinoPoint*, NeutrinoPoint*> x_extremes() const;
    QPair<NeutrinoPoint*, NeutrinoPoint*> y_extremes() const;
    QPair<NeutrinoPoint*, NeutrinoPoint*> z_extremes() const;
    QVector3D event_center() const;

    float get_max_charge() const;

    QJsonObject to_json() const;
    void print() const;

private:
    int id_;
    QList<NeutrinoTrack *> tracks_;
    QPair<NeutrinoPoint*, NeutrinoPoint*> x_axis_extremes_, y_axis_extremes_, z_axis_extremes_;
};
