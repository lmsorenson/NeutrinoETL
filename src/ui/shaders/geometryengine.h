#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QList>
#include <src/ui/geometry/mesh.h>

class GeometryEngine : public QOpenGLFunctions
{
public:
    explicit GeometryEngine();
    virtual ~GeometryEngine();

    void draw_geometry(QOpenGLShaderProgram *program, QMatrix4x4 view_projection_matrix);
    void add_geometry(Mesh * new_mesh);

private:
    QList<Mesh*> mesh_list_;
};