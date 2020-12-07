#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class GeometryEngine : public QOpenGLFunctions
{
public:
    explicit GeometryEngine();
    virtual ~GeometryEngine() = default;

    void draw_geometry(QOpenGLShaderProgram *program);

private:
    void initialize_geometry();

    QOpenGLBuffer index_buffer_;
    QOpenGLBuffer array_buffer_;
};
