#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QSizePolicy>

#include <ui/openglviewport.h>
#include <ui/geometry/cube.h>
#include <models/neutrinopoint.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    front_viewport_ = new Viewport(Axis::X, 0);
    front_viewport_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    right_viewport_ = new Viewport(Axis::Y, -90);
    right_viewport_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    left_viewport_ = new Viewport(Axis::Y, 90);
    left_viewport_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    perspective_viewport_ = new Viewport( {
        AxisRotation(Axis::Y, 45),
        AxisRotation(Axis::X, 30)
    });
    perspective_viewport_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->viewport_grid->addWidget(front_viewport_, 0,0);
    ui->viewport_grid->addWidget(right_viewport_, 0,1);
    ui->viewport_grid->addWidget(left_viewport_, 1,0);
    ui->viewport_grid->addWidget(perspective_viewport_, 1, 1);
}

void MainWindow::add_points(QVector3D view_target, QList<NeutrinoPoint*> points)
{
    qDebug() << view_target;
    engine_ = new GeometryEngine();

    front_viewport_->set_engine(engine_);
    front_viewport_->set_camera_position(view_target);

    right_viewport_->set_engine(engine_);
    right_viewport_->set_camera_position(view_target);

    left_viewport_->set_engine(engine_);
    left_viewport_->set_camera_position(view_target);

    perspective_viewport_->set_engine(engine_);
    perspective_viewport_->set_camera_position(view_target);

//    front_viewport_->create_point(view_target, 1);

    for(auto point : points)
    {
        qDebug() << "point added" << QVector3D(point->x(), point->y(), point->z());
        front_viewport_->create_point(QVector3D(point->x(), point->y(), point->z()), point->charge() * 0.0009);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    delete engine_;
}

