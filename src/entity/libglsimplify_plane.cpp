
#include "libglsimplify_plane.h"

#include "entity/libglsimplify_camera.h"

namespace gl_simplify {

    namespace entity {

        Plane::Plane(const glm::vec3& position)
            : Entity(position)

            , _vbo()
            , _ebo(GL_ELEMENT_ARRAY_BUFFER)
            , _vao()
        {
        }

        Plane::~Plane()
        {
        }

        void Plane::SetSize(GLfloat size)
        {
            _program.Use();
            _program.GetVariable("point_size").SetValue(size);
        }

        bool Plane::Update(GLchar *, GLsizei)
        {
            float vertices[] = {
                -1.0f,  0.0f, -1.0f, 0.0f, 0.0f,  // 0 top left
                 1.0f,  0.0f, -1.0f, 0.0f, 1.0f,  // 1 top right
                 1.0f,  0.0f,  1.0f, 1.0f, 1.0f,  // 2 bottom right
                -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  // 3 bottom left
            };
            unsigned int indices[] = {
                0, 3, 2,  // first Triangle
                2, 1, 0,   // second Triangle
                2, 3, 0,  // first Triangle
                0, 1, 2   // second Triangle
            };

            // upload data and set data format
            _vao.Bind();

            _vbo.Bind();
            _vbo.Upload(sizeof(vertices), vertices, GL_STATIC_DRAW);
            _vbo.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            _vbo.SetAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            _vbo.Unbind();

            _ebo.Bind();
            _ebo.Upload(sizeof(indices), indices, GL_STATIC_DRAW);

            _vao.Unbind();

            return true;
        }

        void Plane::Draw()
        {
            // draw point
            _vao.Bind();

            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

            _vao.Unbind();
        }
    }
}

