#pragma once
#include <QObject>
#include <models/neutrinotrack.h>
#include <models/neutrinoevent.h>

class Deserializer : public QObject
{
    Q_OBJECT
public:
    explicit Deserializer(QObject *parent = nullptr);

    virtual QList<NeutrinoEvent *> deserialize(QString content) = 0;

signals:

};
