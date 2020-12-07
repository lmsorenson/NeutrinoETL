#include "vertex.h"

#include <QDebug>

Vertex::Vertex(QVector3D position, QVector2D texture_coordinates)
    : position_(position)
    , texture_coordinates_(texture_coordinates)
{

}

void Vertex::print()
{
    qDebug() << "Vertex: " << position_;
}
