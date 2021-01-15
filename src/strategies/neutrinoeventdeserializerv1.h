#pragma once
#include <QObject>
#include <models/neutrinoevent.h>
#include <strategies/deserialize.h>

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
