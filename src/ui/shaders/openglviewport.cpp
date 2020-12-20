#include "openglviewport.h"

#include <memory>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <ui/geometry/cube.h>

#include <cmath>

Viewport::Viewport()
: QOpenGLWidget()
, engine_(nullptr)
, texture_(nullptr)
, camera_distance_(6.0f)
{
}

Viewport::~Viewport()
{

    delete engine_;
    delete texture_;
}

void Viewport::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,0);

    init_shaders();
    init_textures();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    if (!engine_)
        engine_ = new GeometryEngine();

    timer_.start(12, this);
}

void Viewport::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 1.0, zFar = 20000.0, fov = 45.0;

    projection_.setToIdentity();

    projection_.perspective(fov, aspect, zNear, zFar);
}

void Viewport::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture_->bind();

    QMatrix4x4 view;
    view.translate(0.0, 0.0, -1 * camera_distance_);
    view.rotate(rotation_);

    engine_->draw_geometry(&program_, projection_ * view);
}

void Viewport::init_shaders()
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

void Viewport::init_textures()
{
    auto image = QImage("../src/ui/shaders/cube.png");
    texture_ = new QOpenGLTexture(image.mirrored());

    texture_->setMinificationFilter(QOpenGLTexture::Nearest);

    texture_->setMagnificationFilter(QOpenGLTexture::Linear);

    texture_->setWrapMode(QOpenGLTexture::Repeat);
}

void Viewport::set_engine(GeometryEngine *engine)
{
    if (engine)
        engine_ = engine;
}

void Viewport::create_point(QVector3D position, float scale)
{
    engine_->add_geometry(new Cube(position, QVector3D(scale, scale, scale)));
}

void Viewport::mousePressEvent(QMouseEvent *e)
{
    mouse_press_position_ = QVector2D(e->localPos());
}

void Viewport::mouseReleaseEvent(QMouseEvent *e)
{
}

void Viewport::mouseMoveEvent(QMouseEvent *e)
{
    qDebug() << e->localPos() << QWidget::size();

    QVector2D diff = (QVector2D(e->localPos()) - mouse_press_position_) / 20;

    mouse_press_position_ = QVector2D(e->localPos());

    rotation_axis_ = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    angular_speed_ = atan(diff.length() / camera_distance_) * (180 / M_PI);
}

void Viewport::timerEvent(QTimerEvent *e)
{
    rotation_ = QQuaternion::fromAxisAndAngle(rotation_axis_, angular_speed_) * rotation_;

    update();

    angular_speed_ = 0;
}
