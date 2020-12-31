#pragma once

#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QBasicTimer>
#include "geometry/geometryengine.h"

enum Axis
{
    X,
    Y,
    Z
};

class AxisRotation
{
public:
    AxisRotation(Axis rotation_axis, float rotation_angle);
    ~AxisRotation() = default;

    float angle() const;
    Axis axis() const;

private:
    float angle_;
    Axis axis_;
};

class Viewport : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    using QOpenGLWidget::QOpenGLWidget;
    explicit Viewport();
    explicit Viewport(Axis axis, float angle);
    explicit Viewport(QList<AxisRotation> rotations);
    virtual ~Viewport();

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void init_shaders();
    void init_textures();

    void set_engine(GeometryEngine *engine);
    void set_camera_position(QVector3D new_position);
    void create_point(QVector3D position, float scale);

    static QVector3D get_axis(Axis axis);

private:
    QBasicTimer timer_;
    QOpenGLShaderProgram program_;
    GeometryEngine *engine_;
    QOpenGLTexture *texture_;

    float camera_distance_;
    QMatrix4x4 projection_;

    QQuaternion camera_rotation_;
    QVector3D camera_position_;

    QVector3D rotation_axis_;
    qreal angular_speed_ = 0;
    QVector2D mouse_press_position_;
signals:

};
