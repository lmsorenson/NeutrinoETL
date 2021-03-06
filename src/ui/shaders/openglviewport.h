#pragma once

#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QBasicTimer>
#include "geometryengine.h"

class OpenGLViewport : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    using QOpenGLWidget::QOpenGLWidget;
    explicit OpenGLViewport();
    virtual ~OpenGLViewport();

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void init_shaders();
    void init_textures();

private:
    QBasicTimer timer_;
    QOpenGLShaderProgram program_;
    GeometryEngine *engine_;
    QOpenGLTexture *texture_;

    float camera_distance_;
    QMatrix4x4 model_;
    QMatrix4x4 view_;
    QMatrix4x4 projection_;

    QQuaternion rotation_;
    QVector3D rotation_axis_;
    qreal angular_speed_ = 0;
    QVector2D mouse_press_position_;
signals:

};
