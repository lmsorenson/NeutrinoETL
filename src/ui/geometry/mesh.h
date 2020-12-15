#pragma once

#include <QObject>
#include <GLFW/glfw3.h>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <src/ui/geometry/vertex.h>

class Mesh : public QObject
{
    Q_OBJECT

public:
    Mesh(QVector3D position = QVector3D(0, 0, 0), QVector3D scale = QVector3D(1, 1, 1));
    virtual ~Mesh();

    virtual Vertex *generate_vertices() = 0;
    virtual GLushort *generate_indices() = 0;
    void allocate();
    void bind();

    QMatrix4x4 model_matrix();

protected:
    Vertex *vertex_array_;
    GLushort *index_array_;

    QOpenGLBuffer index_buffer_;
    QOpenGLBuffer array_buffer_;

    QMatrix4x4 model_matrix_;
    QVector3D position_;
    QVector3D scale_;
};
