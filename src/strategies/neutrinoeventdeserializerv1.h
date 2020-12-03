#pragma once
#include <QObject>
#include <src/models/neutrinoevent.h>
#include <src/strategies/deserialize.h>

class NeutrinoEventDeserializerV1 : public Deserializer
{
    Q_OBJECT
public:
    explicit NeutrinoEventDeserializerV1(QObject *parent = nullptr);

    virtual QList<NeutrinoEvent *> deserialize(QString content) override;
    void on_new_track(NeutrinoEvent * event, QString data);
    void on_new_point(NeutrinoTrack * track, QString data);

signals:

};
