#pragma once

#include <QObject>
#include <QVector3D>
#include <src/ui/geometry/vertex.h>
#include <GLFW/glfw3.h>

class Cube : public QObject
{
    Q_OBJECT
public:
    Cube();
    virtual ~Cube() = default;

    static Vertex *generate_vertices(QVector3D scale = QVector3D(1, 1, 1));
    static GLushort *generate_indices();
};
