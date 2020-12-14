#include "openglviewport.h"

#include <QOpenGLFunctions>
#include <QMouseEvent>

#include <cmath>

OpenGLViewport::OpenGLViewport() : QOpenGLWidget(), engine_(nullptr), texture_(nullptr), camera_distance_(5.0f)
{

}

OpenGLViewport::~OpenGLViewport()
{

}

void OpenGLViewport::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.5,0.5,0.5,1);

    init_shaders();
    init_textures();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    engine_ = new GeometryEngine();

    timer_.start(12, this);
}

void OpenGLViewport::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 1.0, zFar = 10.0, fov = 45.0;

    projection_.setToIdentity();

    projection_.perspective(fov, aspect, zNear, zFar);
}

void OpenGLViewport::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture_->bind();

    {
        QMatrix4x4 view;
        view.translate(-1.5, 0.0, -1 * camera_distance_);
        view.rotate(rotation_);
        program_.setUniformValue("mvp_matrix", projection_ * view);
        program_.setUniformValue("texture", 0);

        engine_->draw_geometry(&program_);
    }

    {
        QMatrix4x4 view;
        view.translate(1.5, 0.0, -1 * camera_distance_);
        view.rotate(rotation_);
        program_.setUniformValue("mvp_matrix", projection_ * view);
        program_.setUniformValue("texture", 0);

        engine_->draw_geometry(&program_);
    }
}

void OpenGLViewport::init_shaders()
{
    if (!program_.addShaderFromSourceFile(QOpenGLShader::Vertex, "../src/ui/shaders/vertex.vsh"))
    {
        qDebug() << "While initializing shaders: vertex shader failed to load.";
        close();
    }

    if (!program_.addShaderFromSourceFile(QOpenGLShader::Fragment, "../src/ui/shaders/fragment.fsh"))
    {
        qDebug() << "While initializing shaders: fragment shader failed to load.";
        close();
    }

    if (!program_.link())
    {
        qDebug() << "While initializing shaders: program link command failed.";
        close();
    }

    if (!program_.bind())
    {
        qDebug() << "While initializing shaders: program bind failed.";
        close();
    }
}

void OpenGLViewport::init_textures()
{
    auto image = QImage("../src/ui/shaders/cube.png");
    texture_ = new QOpenGLTexture(image.mirrored());

    texture_->setMinificationFilter(QOpenGLTexture::Nearest);

    texture_->setMagnificationFilter(QOpenGLTexture::Linear);

    texture_->setWrapMode(QOpenGLTexture::Repeat);
}

void OpenGLViewport::mousePressEvent(QMouseEvent *e)
{
    mouse_press_position_ = QVector2D(e->localPos());
}

void OpenGLViewport::mouseReleaseEvent(QMouseEvent *e)
{
}

void OpenGLViewport::mouseMoveEvent(QMouseEvent *e)
{
    qDebug() << e->localPos() << QWidget::size();

    QVector2D diff = (QVector2D(e->localPos()) - mouse_press_position_) / 20;

    mouse_press_position_ = QVector2D(e->localPos());

    rotation_axis_ = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    angular_speed_ = atan(diff.length() / camera_distance_) * (180 / M_PI);
}

void OpenGLViewport::timerEvent(QTimerEvent *e)
{
    rotation_ = QQuaternion::fromAxisAndAngle(rotation_axis_, angular_speed_) * rotation_;

    update();

    angular_speed_ = 0;
}
