
#include "libglsimplify_gl_point.h"

#include "entity/libglsimplify_camera.h"

namespace gl_simplify {

    namespace entity {

        namespace point {

            GLPoint::GLPoint(const glm::vec3& position)
                : Entity(position)

                , _vbo()
                , _ebo(GL_ELEMENT_ARRAY_BUFFER)
                , _vao()
            {
                glEnable(GL_PROGRAM_POINT_SIZE);
            }

            GLPoint::~GLPoint()
            {
            }

            void GLPoint::SetSize(GLfloat size)
            {
                _program.Use();
                _program.GetVariable("point_size").SetValue(size);
            }

            bool GLPoint::Initialize(GLchar *error, GLsizei error_length)
            {
                float vertices[] = {
                    0.0f,  0.0f, 0.0f
                };
                unsigned int indices[] = {
                    0
                };

                _vao.Bind();

                _vbo.Bind();
                _vbo.Upload(sizeof(vertices), vertices, GL_STATIC_DRAW);
                _vbo.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                _vbo.Unbind();

                _ebo.Bind();
                _ebo.Upload(sizeof(indices), indices, GL_STATIC_DRAW);

                _vao.Unbind();
                
                _vertex_shader = new core::VertexShader();
                _vertex_shader->source << "layout (location = 0) in vec3 model_position;";

                _vertex_shader->source << "uniform float point_size;";

                _vertex_shader->source << "uniform mat4 model;";
                _vertex_shader->source << "uniform mat4 view;";
                _vertex_shader->source << "uniform mat4 projection;";

                _vertex_shader->source << "void main()";
                _vertex_shader->source << "{" ;
                _vertex_shader->source << "   vec4 view_position = view * model * vec4(model_position, 1.0);";
                _vertex_shader->source << "   gl_Position = projection * view_position;";
                _vertex_shader->source << "   gl_PointSize = point_size / length(view_position.xyz);";
                _vertex_shader->source << "}";

                return _vertex_shader->Compile(error, error_length);
            }

            void GLPoint::Render(Camera* camera)
            {
                // use program, begin to update program variables
                _program.Use();

                _program.GetVariable("model").SetMat(_model_transform);
                _program.GetVariable("view").SetMat(camera->GetView());
                _program.GetVariable("projection").SetMat(camera->GetProjection());

                // update shader veriables
                _vertex_shader->Update(_program);
                _attatch_shader->Update(_program);

                // draw point
                _vao.Bind();

                glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);

                _vao.Unbind();
            }
        }
    }
}

