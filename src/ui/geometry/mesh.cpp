#include "mesh.h"

Mesh::Mesh(QVector3D position, QVector3D scale)
: index_buffer_(QOpenGLBuffer::IndexBuffer)
, index_array_(nullptr)
, vertex_array_(nullptr)
, model_matrix_()
, position_(position)
, scale_(scale)
{
    index_buffer_.create();
    array_buffer_.create();

    model_matrix_.translate(position);
}

Mesh::~Mesh()
{
    delete[] vertex_array_;
    delete[] index_array_;
}

void Mesh::allocate()
{
    Vertex *vertices = generate_vertices();
    GLushort *indices = generate_indices();

    array_buffer_.bind();
    array_buffer_.allocate(vertices, 24 * sizeof(Vertex));

    index_buffer_.bind();
    index_buffer_.allocate(indices, 34 * sizeof(GLushort));
}

void Mesh::bind()
{
    array_buffer_.bind();
    index_buffer_.bind();
}

QMatrix4x4 Mesh::model_matrix()
{
    return model_matrix_;
}