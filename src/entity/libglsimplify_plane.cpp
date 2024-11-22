
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

        bool Plane::Initialize(GLchar *error, GLsizei error_length)
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

            _vao.Bind();

            _vbo.Bind();
            _vbo.Upload(sizeof(vertices), vertices, GL_STATIC_DRAW);
            _vbo.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            _vbo.SetAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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

        void Plane::Render(Camera* camera)
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

            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

            _vao.Unbind();
        }
    }
}

