#include <src/ui/mainwindow.h>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextCodec>

#include <src/models/neutrinotrack.h>

void on_new_track(NeutrinoTrack * track, QString data, QString path);
void on_new_point(NeutrinoTrack * track, QString data);

int main(int argc, char *argv[])
{
    qDebug() << "argc " << argc;
    for(int i = 0; i < argc; ++i)
    {
        qDebug() << "argument " << i + 1 << ": " << argv[i];
    }

    QFile file("../sample-data/information.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    auto text = file.readAll();
    auto array = text.split('\n');


    NeutrinoTrack *current_track = nullptr;
    for(int i = 0; i < array.size(); ++i)
    {
        qDebug() << i;
        auto id_prefix = QString("track ID");
        auto prefix = QString("Point no");
        auto record = QString(array[i]);

        if (record.startsWith(id_prefix))
            on_new_track(current_track, QStringRef(&record, id_prefix.size(), record.size() - id_prefix.size()).toString(), "");

        if (record.startsWith(prefix))
            on_new_point(current_track, QStringRef(&record, prefix.size(), record.size() - prefix.size()).toString());
    }

    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

    return 0;
}

void on_new_track(NeutrinoTrack * track, QString data, QString path)
{
    qDebug() << data;

    if (track)
    {
        track->to_disk(path);
        delete track;
        track = nullptr;
    }

    bool ok;
    auto id = data.trimmed().toInt(&ok);

    if (ok)
        track = new NeutrinoTrack(id);
}

void on_new_point(NeutrinoTrack * track, QString data)
{
    bool ok;
    QMap<QString, float> map = QMap<QString, float>();
    auto parts = data.trimmed().split(" ");

    float point_no = parts.takeFirst().toFloat(&ok);
    if (!ok) return;

    qDebug() << "Label: " << "Point no" << " Value: " << point_no;
    map.insert("Point no", point_no);

    for(int i = 0; i+1 < parts.size(); i += 2)
    {
        auto label = parts[i];
        float value = parts[i+1].toFloat(&ok);
        if (!ok) return;

        qDebug() << "Label: " << label << " Value: " << value;
        map.insert(label, value);
    }

    qDebug() << "new point";
    track->add_point(new NeutrinoPoint(map));
}
