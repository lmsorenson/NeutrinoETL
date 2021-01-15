#include "cube.h"


Cube::Cube(QVector3D position, QVector3D scale)
: Mesh(position, scale)
{
}

Cube::~Cube()
{
}

Vertex *Cube::generate_vertices()
{
    vertex_array_ = new Vertex[24]{
        Vertex(QVector3D(-1.0f, -1.0f,  1.0f) * scale_, QVector2D(0.0f, 0.0f)),
        Vertex(QVector3D( 1.0f, -1.0f,  1.0f) * scale_, QVector2D(0.33f, 0.0f)),
        Vertex(QVector3D(-1.0f,  1.0f,  1.0f) * scale_, QVector2D(0.0f, 0.5f)),
        Vertex(QVector3D( 1.0f,  1.0f,  1.0f) * scale_, QVector2D(0.33f, 0.5f)),

        Vertex(QVector3D( 1.0f, -1.0f,  1.0f) * scale_, QVector2D( 0.0f, 0.5f)),
        Vertex(QVector3D( 1.0f, -1.0f, -1.0f) * scale_, QVector2D(0.33f, 0.5f)),
        Vertex(QVector3D( 1.0f,  1.0f,  1.0f) * scale_, QVector2D(0.0f, 1.0f)),
        Vertex(QVector3D( 1.0f,  1.0f, -1.0f) * scale_, QVector2D(0.33f, 1.0f)),

        Vertex(QVector3D( 1.0f, -1.0f, -1.0f) * scale_, QVector2D(0.66f, 0.5f)),
        Vertex(QVector3D(-1.0f, -1.0f, -1.0f) * scale_, QVector2D(1.0f, 0.5f)),
        Vertex(QVector3D( 1.0f,  1.0f, -1.0f) * scale_, QVector2D(0.66f, 1.0f)),
        Vertex(QVector3D(-1.0f,  1.0f, -1.0f) * scale_, QVector2D(1.0f, 1.0f)),

        Vertex(QVector3D(-1.0f, -1.0f, -1.0f) * scale_, QVector2D(0.66f, 0.0f)),
        Vertex(QVector3D(-1.0f, -1.0f,  1.0f) * scale_, QVector2D(1.0f, 0.0f)),
        Vertex(QVector3D(-1.0f,  1.0f, -1.0f) * scale_, QVector2D(0.66f, 0.5f)),
        Vertex(QVector3D(-1.0f,  1.0f,  1.0f) * scale_, QVector2D(1.0f, 0.5f)),

        Vertex(QVector3D(-1.0f, -1.0f, -1.0f) * scale_, QVector2D(0.33f, 0.0f)),
        Vertex(QVector3D( 1.0f, -1.0f, -1.0f) * scale_, QVector2D(0.66f, 0.0f)),
        Vertex(QVector3D(-1.0f, -1.0f,  1.0f) * scale_, QVector2D(0.33f, 0.5f)),
        Vertex(QVector3D( 1.0f, -1.0f,  1.0f) * scale_, QVector2D(0.66f, 0.5f)),

        Vertex(QVector3D(-1.0f,  1.0f,  1.0f) * scale_, QVector2D(0.33f, 0.5f)),
        Vertex(QVector3D( 1.0f,  1.0f,  1.0f) * scale_, QVector2D(0.66f, 0.5f)),
        Vertex(QVector3D(-1.0f,  1.0f, -1.0f) * scale_, QVector2D(0.33f, 1.0f)),
        Vertex(QVector3D( 1.0f,  1.0f, -1.0f) * scale_, QVector2D(0.66f, 1.0f))
    };

    return vertex_array_;
}

GLushort *Cube::generate_indices()
{
    index_array_ = new GLushort [34]{
             0,  1,  2,  3,  3,
             4,  4,  5,  6,  7,  7,
             8,  8,  9, 10, 11, 11,
            12, 12, 13, 14, 15, 15,
            16, 16, 17, 18, 19, 19,
            20, 20, 21, 22, 23
    };

    return index_array_;
}
