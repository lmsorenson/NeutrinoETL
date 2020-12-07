#include "geometryengine.h"

#include <src/ui/geometry/vertex.h>
#include <src/ui/geometry/cube.h>


GeometryEngine::GeometryEngine()
    : index_buffer_(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    index_buffer_.create();
    array_buffer_.create();

    initialize_geometry();
}

void GeometryEngine::draw_geometry(QOpenGLShaderProgram *program)
{
    array_buffer_.bind();
    index_buffer_.bind();

    quintptr offset = 0;

    int position_location = program->attributeLocation("a_position");
    program->enableAttributeArray(position_location);
    program->setAttributeBuffer(position_location, GL_FLOAT, offset, 3, sizeof(Vertex));

    offset += sizeof(QVector3D);

    int texture_coordinate_location = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texture_coordinate_location);
    program->setAttributeBuffer(texture_coordinate_location, GL_FLOAT, offset, 2, sizeof(Vertex));

    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, nullptr);
}

void GeometryEngine::initialize_geometry()
{
    Vertex vertices[] =
    {
        Vertex(QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)),
        Vertex(QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)),
        Vertex(QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)),
        Vertex(QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)),

        Vertex(QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)),
        Vertex(QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)),
        Vertex(QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)),
        Vertex(QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)),

        Vertex(QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)),
        Vertex(QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)),
        Vertex(QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)),
        Vertex(QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)),

        Vertex(QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)),
        Vertex(QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)),
        Vertex(QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)),
        Vertex(QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)),

        Vertex(QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)),
        Vertex(QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)),
        Vertex(QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)),
        Vertex(QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)),

        Vertex(QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)),
        Vertex(QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)),
        Vertex(QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)),
        Vertex(QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f))
    };

    for(int i=0; i < 24; ++i)
    {
        vertices[i].print();
    }


    array_buffer_.bind();
    array_buffer_.allocate(vertices, 24 * sizeof(Vertex));

    GLushort indices[] = {
             0,  1,  2,  3,  3,
             4,  4,  5,  6,  7,  7,
             8,  8,  9, 10, 11, 11,
            12, 12, 13, 14, 15, 15,
            16, 16, 17, 18, 19, 19,
            20, 20, 21, 22, 23
    };

    index_buffer_.bind();
    index_buffer_.allocate(indices, 34 * sizeof(GLushort));
}

