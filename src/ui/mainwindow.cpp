#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <ui/shaders/openglviewport.h>
#include <ui/geometry/cube.h>
#include <models/neutrinopoint.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    front_viewport_ = new Viewport(Axis::X, 0);
    right_viewport_ = new Viewport(Axis::Y, -90);
    left_viewport_ = new Viewport(Axis::Y, 90);
    perspective_viewport_ = new Viewport( {
        AxisRotation(Axis::Y, 45),
        AxisRotation(Axis::X, 30)
    });

    ui->gridLayout->addWidget(front_viewport_, 0,0);
    ui->gridLayout->addWidget(right_viewport_, 0,1);
    ui->gridLayout->addWidget(left_viewport_, 1,0);
    ui->gridLayout->addWidget(perspective_viewport_, 1, 1);
}

void MainWindow::add_points(QList<NeutrinoPoint*> points)
{
//    for(auto point : points)
//    {
//        viewport_->create_point(QVector3D(point->x(), point->y(), point->z()), point->charge() * .001);
//    }
    engine_ = new GeometryEngine();

    front_viewport_->set_engine(engine_);
    right_viewport_->set_engine(engine_);
    left_viewport_->set_engine(engine_);
    perspective_viewport_->set_engine(engine_);

    front_viewport_->create_point(QVector3D(0, 0, 0), 1);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete engine_;
}

