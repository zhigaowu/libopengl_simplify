
#include "libglsimplify_plane.h"

namespace gl_simplify {

    namespace entity::basic {
        const VertexDataBuffer &Plane::dafaultVertextDataBuffer()
        {
            static VertexDataBuffer vertexDataBuffer = {
                VertexData{glm::vec3(-1.0f,  0.0f, -1.0f), glm::vec3(0.0f,  1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},  // 0 top left
                VertexData{glm::vec3( 1.0f,  0.0f, -1.0f), glm::vec3(0.0f,  1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},  // 1 top right
                VertexData{glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3(0.0f,  1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},  // 2 bottom right
                VertexData{glm::vec3(-1.0f,  0.0f,  1.0f), glm::vec3(0.0f,  1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},  // 3 bottom left
                
                VertexData{glm::vec3(-1.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},  // 4 top left
                VertexData{glm::vec3( 1.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},  // 5 top right
                VertexData{glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},  // 6 bottom right
                VertexData{glm::vec3(-1.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},  // 7 bottom left
            };

            return vertexDataBuffer;
        }

        const IndexBuffer &Plane::defaultIndexBuffer()
        {
            static IndexBuffer indices = {
                0, 3, 2,  // first Triangle
                2, 1, 0,   // second Triangle
                6, 7, 4,  // first Triangle
                4, 5, 6   // second Triangle
            };

            return indices;
        }

        Plane::Plane()
            : BaseEntity()
        {
        }

        Plane::~Plane()
        {
        }

        void Plane::Render()
        {
            _vao->Bind();

            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
            
            _vao->Unbind();
        }

    }
}

