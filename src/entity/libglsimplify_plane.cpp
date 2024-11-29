
#include "libglsimplify_plane.h"

namespace gl_simplify {

    namespace entity {

        Plane::Plane(const glm::vec3& position)
            : Entity(position)
        {
        }

        Plane::~Plane()
        {
        }

        void Plane::Create()
        {
            static GLfloat vertices[] = {
                -1.0f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,  // 0 top left
                 1.0f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,  // 1 top right
                 1.0f,  0.0f,  1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f,  // 2 bottom right
                -1.0f,  0.0f,  1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,  // 3 bottom left
                
                -1.0f,  0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // 4 top left
                 1.0f,  0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,  // 5 top right
                 1.0f,  0.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // 6 bottom right
                -1.0f,  0.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // 7 bottom left
            };
            
            static GLuint indices[] = {
                0, 3, 2,  // first Triangle
                2, 1, 0,   // second Triangle
                6, 7, 4,  // first Triangle
                4, 5, 6   // second Triangle
            };

            _vertices.resize(sizeof(vertices) / sizeof(GLfloat));
            _indices.resize(sizeof(indices) / sizeof(GLuint));

            memcpy(_vertices.data(), vertices, sizeof(vertices));
            memcpy(_indices.data(), indices, sizeof(indices));

            createDefaultArrays();

            bindDefaultVertexLayout();
        }
    }
}

