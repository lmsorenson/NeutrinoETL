#include <src/ui/mainwindow.h>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextCodec>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <src/strategies/neutrinoeventdeserializerv1.h>

int main(int argc, char *argv[])
{
    if (argc < 3) return 1;
    auto deserializer = new NeutrinoEventDeserializerV1();

    auto read_path = argv[argc-2];
    auto write_path = argv[argc-1];

    qDebug() << "argc " << argc;
    for(int i = 0; i < argc;)
    {
        qDebug() << "argument " << i + 1 << ": " << argv[i];

        ++i;
    }

    QFile file(read_path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (file.isOpen())
    {
        auto events = deserializer->deserialize(file.readAll());

        QJsonArray json_array;

        for (int i=0; i < events.size(); ++i)
            json_array.append(events[i]->to_json());

        QJsonDocument document(json_array);
        QFile out_file(write_path);
        out_file.open(QIODevice::WriteOnly | QIODevice::Text);

        QTextStream out(&out_file);
        out << document.toJson();
        out_file.close();

        QApplication a(argc, argv);
        //    MainWindow w;
        //    w.show();
        //    return a.exec();

        return 0;
    }
    else
    {
        return 1;
    }
}

