#pragma once

#include <QObject>
#include <QList>
#include <QVector3D>
#include <src/models/neutrinopoint.h>


class NeutrinoTrack : public QObject
{
    Q_OBJECT

public:
    NeutrinoTrack(int id);
    virtual ~NeutrinoTrack();

    QJsonObject to_json();
    void add_point(NeutrinoPoint *point);

    QList<NeutrinoPoint*> get_points();
    float get_max_charge();
    void print();

private:
    int id_;
    QList<NeutrinoPoint*> points_;
};
