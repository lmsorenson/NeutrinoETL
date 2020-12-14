#pragma once

#include <QObject>
#include <QList>
#include <src/models/neutrinopoint.h>

class NeutrinoTrack : QObject
{
    Q_OBJECT

public:
    NeutrinoTrack(int id);
    virtual ~NeutrinoTrack();

    QJsonObject to_json();
    void add_point(NeutrinoPoint *point);

    float get_max_charge();

    void print();

private:
    int id_;
    QList<NeutrinoPoint *> points_;
};
