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



    viewport_ = new Viewport();
    side_viewport_ = new Viewport();



    ui->gridLayout->addWidget(viewport_);
    ui->gridLayout->addWidget(side_viewport_);
}

void MainWindow::add_points(QList<NeutrinoPoint*> points)
{
//    for(auto point : points)
//    {
//        viewport_->create_point(QVector3D(point->x(), point->y(), point->z()), point->charge() * .001);
//    }
    GeometryEngine *engine = new GeometryEngine();

    viewport_->set_engine(engine);
    side_viewport_->set_engine(engine);

    viewport_->create_point(QVector3D(0, 0, 0), 1);
}


MainWindow::~MainWindow()
{
    delete ui;
}

