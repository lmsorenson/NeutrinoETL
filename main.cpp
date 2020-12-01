#include <src/ui/mainwindow.h>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextCodec>

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

    for(int i = 0; i < array.size(); ++i)
    {
        auto id_prefix = QString("track ID");
        auto prefix = QString("Point no");
        auto record = QString(array[i]);

        if (record.startsWith(id_prefix))
        {
            QStringRef sub_string(&record, id_prefix.size(), record.size() - id_prefix.size());
            qDebug() << "------- NEW TRACK -------";
            qDebug() << sub_string.toString();
        }

        if (record.startsWith(prefix))
        {
            QStringRef subString(&record, prefix.size(), record.size() - prefix.size());
            qDebug() << subString.toString();
        }
    }

    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

    return 0;
}
