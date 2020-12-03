#include "neutrinoeventdeserializerv1.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <src/models/neutrinoevent.h>

NeutrinoEventDeserializerV1::NeutrinoEventDeserializerV1(QObject *parent) : Deserializer(parent)
{

}

QList<NeutrinoEvent *> NeutrinoEventDeserializerV1::deserialize(QString content)
{
    auto array = content.split('\n');

    QList<NeutrinoEvent*> event_list = QList<NeutrinoEvent*>();
    for(int i = 0; i < array.size(); ++i)
    {
        auto event_prefix = QString("event ID");
        auto id_prefix = QString("track ID");
        auto prefix = QString("Point no");
        auto record = QString(array[i]).trimmed();

        if (record.startsWith(event_prefix))
        {
            bool ok;
            int event_id = QStringRef(&record, event_prefix.size(), record.size() - event_prefix.size()).toInt(&ok);

            if (!ok) break;

            event_list.append(new NeutrinoEvent(event_id));
        }

        if (record.startsWith(id_prefix))
            this->on_new_track(event_list.last(), QStringRef(&record, id_prefix.size(), record.size() - id_prefix.size()).toString());

        if (record.startsWith(prefix) && !event_list.isEmpty())
        {
            auto latest_track = event_list.last();
            this->on_new_point(latest_track->last(), QStringRef(&record, prefix.size(), record.size() - prefix.size()).toString());
        }
    }

    for (int i=0; i < event_list.size(); ++i)
        event_list[i]->print();

    return event_list;
}

void NeutrinoEventDeserializerV1::on_new_track(NeutrinoEvent * event, QString data)
{
    bool ok;
    auto id = data.trimmed().toInt(&ok);

    if (ok && event)
    {
        event->add_track(new NeutrinoTrack(id));
    }
}

void NeutrinoEventDeserializerV1::on_new_point(NeutrinoTrack *track, QString data)
{
    if (track == nullptr) return;

    bool ok;
    QMap<QString, float> map = QMap<QString, float>();
    auto parts = data.trimmed().split(" ");

    float point_no = parts.takeFirst().toFloat(&ok);
    if (!ok) return;

    map.insert("Point no", point_no);

    for(int i = 0; i+1 < parts.size(); i += 2)
    {
        auto label = parts[i];
        float value = parts[i+1].toFloat(&ok);
        if (!ok) return;

        map.insert(label, value);
    }

    track->add_point(new NeutrinoPoint(map));
}
