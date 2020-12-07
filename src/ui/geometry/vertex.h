#pragma once

#include <QVector3D>
#include <QVector2D>

class Vertex
{
public:
    explicit Vertex(QVector3D position, QVector2D texture_coordinates);

    void print();

private:
    QVector3D position_;
    QVector2D texture_coordinates_;
};
