#include "geometryengine.h"

#include <src/ui/geometry/vertex.h>
#include <src/ui/geometry/mesh.h>


GeometryEngine::GeometryEngine()
{
    initializeOpenGLFunctions();
}

GeometryEngine::~GeometryEngine()
{
    for(int i = 0; i < mesh_list_.size(); ++i)
    {
        delete mesh_list_[i];
    }

    mesh_list_.clear();
}

void GeometryEngine::draw_geometry(QOpenGLShaderProgram *program, QMatrix4x4 view_projection_matrix)
{
    for(auto mesh : mesh_list_)
    {
        program->setUniformValue("mvp_matrix", view_projection_matrix * mesh->model_matrix());
        program->setUniformValue("texture", 0);
        mesh->bind();

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
}

void GeometryEngine::add_geometry(Mesh *new_mesh)
{
    new_mesh->allocate();
    mesh_list_ << new_mesh;
}

