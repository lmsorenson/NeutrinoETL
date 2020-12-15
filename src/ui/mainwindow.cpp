#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <src/ui/shaders/openglviewport.h>
#include <src/models/neutrinopoint.h>

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

    viewport_->create_point(QVector3D(), 1);
    side_viewport_->create_point(QVector3D(), 1);
}


MainWindow::~MainWindow()
{
    delete ui;
}

