#pragma once

#include <QObject>
#include <GLFW/glfw3.h>
#include <QVector3D>
#include <src/ui/geometry/vertex.h>
#include <src/ui/geometry/mesh.h>

class Cube : public Mesh
{
    Q_OBJECT
public:
    Cube(QVector3D position = QVector3D(0, 0, 0), QVector3D scale = QVector3D(1, 1, 1));
    virtual ~Cube();

    virtual Vertex *generate_vertices() override;
    virtual GLushort *generate_indices() override;

private:
};
