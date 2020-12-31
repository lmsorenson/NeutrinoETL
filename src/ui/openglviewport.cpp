#include "openglviewport.h"

#include <memory>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <ui/geometry/geometryengine.h>
#include <ui/geometry/cube.h>

#include <cmath>

Viewport::Viewport()
: QOpenGLWidget()
, engine_(nullptr)
, texture_(nullptr)
, camera_distance_(450)
, camera_position_(QVector3D())
{

}

Viewport::Viewport(Axis axis, float angle) : Viewport()
{
    camera_rotation_ = QQuaternion::fromAxisAndAngle(Viewport::get_axis(axis), angle);
}

Viewport::Viewport(QList<AxisRotation> rotations) : Viewport()
{
    for (auto rotation : rotations)
    {
        auto axis = rotation.axis();
        camera_rotation_ = QQuaternion::fromAxisAndAngle(Viewport::get_axis(axis), rotation.angle()) * camera_rotation_;
    }
}

QVector3D Viewport::get_axis(Axis axis)
{
    switch (axis)
    {
        case Axis::X: return QVector3D(1, 0, 0);
        case Axis::Y: return QVector3D(0, 1, 0);
        default:
        case Axis::Z: return QVector3D(0, 0, 1);
    }
}

Viewport::~Viewport()
{
    delete texture_;
}

void Viewport::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(.5,.5,.5,1);

    init_shaders();
    init_textures();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    if (!engine_) engine_ = new GeometryEngine();

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

    QMatrix4x4 model;
    model.translate(-1 * camera_position_);

    QMatrix4x4 view;
    view.translate(0, 0, -1 * camera_distance_);
    view.rotate(camera_rotation_);

    if (engine_) engine_->draw_geometry(&program_, projection_ * view * model);
}

void Viewport::init_shaders()
{
    if (!program_.addShaderFromSourceFile(QOpenGLShader::Vertex, "../../src/ui/shaders/vertex.vsh"))
    {
        qDebug() << "While initializing shaders: vertex shader failed to load.";
        close();
    }

    if (!program_.addShaderFromSourceFile(QOpenGLShader::Fragment, "../../src/ui/shaders/fragment.fsh"))
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
    auto image = QImage("../../src/ui/shaders/cube.png");
    texture_ = new QOpenGLTexture(image.mirrored());

    texture_->setMinificationFilter(QOpenGLTexture::Nearest);

    texture_->setMagnificationFilter(QOpenGLTexture::Linear);

    texture_->setWrapMode(QOpenGLTexture::Repeat);
}

void Viewport::set_engine(GeometryEngine *engine)
{
    if (engine)
    {
        delete engine_;
        engine_ = engine;
    }
}

void Viewport::set_camera_position(QVector3D new_position)
{
    camera_position_ = new_position;
}

void Viewport::create_point(QVector3D position, float scale)
{
    if (engine_) engine_->add_geometry(new Cube(position, QVector3D(scale, scale, scale)));
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
    camera_rotation_ = QQuaternion::fromAxisAndAngle(rotation_axis_, angular_speed_) * camera_rotation_;

    update();

    angular_speed_ = 0;
}

AxisRotation::AxisRotation(Axis rotation_axis, float rotation_angle) : axis_(rotation_axis), angle_(rotation_angle){}
float AxisRotation::angle() const { return angle_; }
Axis AxisRotation::axis() const { return axis_; }