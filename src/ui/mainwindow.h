#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void add_points(QVector3D view_target, QList<class NeutrinoPoint*> points);

private:
    Ui::MainWindow *ui;

    class Viewport *front_viewport_, *right_viewport_ ,*left_viewport_, *perspective_viewport_;
    class GeometryEngine * engine_;
};
