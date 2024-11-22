
#include "libglsimplify_cube.h"

#include "entity/libglsimplify_camera.h"

namespace gl_simplify {

    namespace entity {

        Cube::Cube(const glm::vec3& position)
            : Entity(position)

            , _vbo()
            , _ebo(GL_ELEMENT_ARRAY_BUFFER)
            , _vao()
        {
        }

        Cube::~Cube()
        {
        }

        bool Cube::Initialize(GLchar *error, GLsizei error_length)
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

            _vao.Bind();

            _vbo.Bind();
            _vbo.Upload(sizeof(vertices), vertices, GL_STATIC_DRAW);
            _vbo.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            _vbo.SetAttribute(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            _vbo.Unbind();

            _ebo.Bind();
            _ebo.Upload(sizeof(indices), indices, GL_STATIC_DRAW);

            _vao.Unbind();
            
            _vertex_shader = new core::VertexShader(_program);
            _vertex_shader->source << "layout (location = 0) in vec3 model_position;";
            _vertex_shader->source << "layout (location = 1) in vec2 texture_position;";

            _vertex_shader->source << "uniform mat4 model;";
            _vertex_shader->source << "uniform mat4 view;";
            _vertex_shader->source << "uniform mat4 projection;";

            _vertex_shader->source << "out vec2 TexCoord;";

            _vertex_shader->source << "void main()";
            _vertex_shader->source << "{" ;
            _vertex_shader->source << "   gl_Position = projection * view * model * vec4(model_position, 1.0);";
            _vertex_shader->source << "   TexCoord = vec2(texture_position.x, 1.0 - texture_position.y);";
            _vertex_shader->source << "}";

            return _vertex_shader->Compile(error, error_length);
        }

        void Cube::Render(Camera* camera)
        {
            // use program, begin to update program variables
            _program.Use();

            _program.GetVariable("model").SetMat(_model_transform);
            _program.GetVariable("view").SetMat(camera->GetView());
            _program.GetVariable("projection").SetMat(camera->GetProjection());

            // update shader veriables
            _vertex_shader->Update();
            _attatch_shader->Update();

            // draw point
            _vao.Bind();

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            _vao.Unbind();
        }
    }
}

