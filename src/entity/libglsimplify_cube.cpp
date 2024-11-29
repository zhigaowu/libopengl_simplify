
#include "libglsimplify_cube.h"

namespace gl_simplify {

    namespace entity {

        Cube::Cube(const glm::vec3& position)
            : Entity(position)
        {
        }

        Cube::~Cube()
        {
        }

        void Cube::Create()
        {
            static float vertices[] = {
                // Positions          // Normals           // Texture Coords
                // Front face
                -1.0f, -1.0f,  1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // 0
                 1.0f, -1.0f,  1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f, // 1
                 1.0f,  1.0f,  1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f, // 2
                -1.0f,  1.0f,  1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, // 3

                // Back face
                -1.0f, -1.0f, -1.0f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, // 4
                 1.0f, -1.0f, -1.0f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f, // 5
                 1.0f,  1.0f, -1.0f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f, // 6
                -1.0f,  1.0f, -1.0f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f, // 7

                // Left face
                -1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // 8
                -1.0f, -1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // 9
                -1.0f,  1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // 10
                -1.0f,  1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // 11

                // Right face
                 1.0f, -1.0f, -1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // 12
                 1.0f, -1.0f,  1.0f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // 13
                 1.0f,  1.0f,  1.0f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // 14
                 1.0f,  1.0f, -1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // 15

                // Top face
                -1.0f,  1.0f, -1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f, // 16
                 1.0f,  1.0f, -1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f, // 17
                 1.0f,  1.0f,  1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f, // 18
                -1.0f,  1.0f,  1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // 19

                // Bottom face
                -1.0f, -1.0f, -1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, // 20
                 1.0f, -1.0f, -1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f, // 21
                 1.0f, -1.0f,  1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f, // 22
                -1.0f, -1.0f,  1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f  // 23
            };

            static unsigned int indices[] = {
                // Front face
                0, 1, 2, 0, 2, 3,
                // Back face
                4, 7, 6, 4, 6, 5,
                // Left face
                8, 9, 10, 8, 10, 11,
                // Right face
                13, 12, 15, 13, 15, 14,
                // Top face
                16, 19, 18, 18, 17, 16,
                // Bottom face
                20, 21, 22, 20, 22, 23
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

