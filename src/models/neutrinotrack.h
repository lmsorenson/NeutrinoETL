#pragma once

#include <QObject>
#include <QList>
#include <src/models/neutrinopoint.h>

class NeutrinoTrack : QObject
{
    Q_OBJECT

public:
    NeutrinoTrack(int id);
    virtual ~NeutrinoTrack() = default;

    void to_disk(QString path);
    void add_point(NeutrinoPoint *point);

    int id_;
    QList<NeutrinoPoint *> points_;
};
