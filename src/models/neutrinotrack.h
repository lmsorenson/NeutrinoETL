#pragma once

#include <QObject>
#include <QList>
#include <QVector3D>
#include <models/neutrinopoint.h>

class NeutrinoTrack : public QObject
{
    Q_OBJECT

public:
    NeutrinoTrack(int id);
    virtual ~NeutrinoTrack();

    void add_point(NeutrinoPoint *point);

    QList<NeutrinoPoint*> get_points() const;
    QPair<NeutrinoPoint*, NeutrinoPoint*> x_extremes() const;
    QPair<NeutrinoPoint*, NeutrinoPoint*> y_extremes() const;
    QPair<NeutrinoPoint*, NeutrinoPoint*> z_extremes() const;
    QVector3D track_center() const;

    double get_max_charge() const;
    double total_charge() const;
    double track_density() const;
    void calculate_extremes();

    int32_t id() const;

    QJsonObject to_json() const;
    void print() const;

private:
    int32_t id_;
    QList<NeutrinoPoint*> points_;
    QPair<NeutrinoPoint*, NeutrinoPoint*> x_axis_extremes_, y_axis_extremes_, z_axis_extremes_;
};
