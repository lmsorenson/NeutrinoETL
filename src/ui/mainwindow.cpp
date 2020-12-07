#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <src/ui/shaders/openglviewport.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gridLayout->addWidget(new OpenGLViewport());
}


MainWindow::~MainWindow()
{
    delete ui;
}

