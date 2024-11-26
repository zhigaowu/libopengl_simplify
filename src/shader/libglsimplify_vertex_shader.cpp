
#include "libglsimplify_vertex_shader.h"

#include "entity/libglsimplify_camera.h"

#include "core/libglsimplify_program.h"

namespace gl_simplify {

    namespace shader {

        const std::string VertexShader::MODEL_VARIABLE_NAME = "model";
        const std::string VertexShader::VIEW_VARIABLE_NAME = "view";
        const std::string VertexShader::PROJECTION_VARIABLE_NAME = "projection";

        GLint VertexShader::MaxVertexAttributesSupported()
        {
            GLint value = 0;
            glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
            return value;
        }

        VertexShader::VertexShader(entity::Entity* entity)
            : Shader(entity->GetProgram(), GL_VERTEX_SHADER)
            , _entity(entity)
            , _camera(nullptr)
        {
            
            source << "layout (location = 0) in vec3 model_position;";
            source << "layout (location = 1) in vec2 texture_position;";

            source << "uniform mat4 " << MODEL_VARIABLE_NAME <<";";
            source << "uniform mat4 " << VIEW_VARIABLE_NAME <<";";
            source << "uniform mat4 " << PROJECTION_VARIABLE_NAME <<";";

            source << "out vec2 TexCoord;";

            source << "void main()";
            source << "{" ;
            source << "   gl_Position = " << PROJECTION_VARIABLE_NAME << " * " << VIEW_VARIABLE_NAME << " * " << MODEL_VARIABLE_NAME <<" * vec4(model_position, 1.0);";
            source << "   TexCoord = vec2(texture_position.x, 1.0 - texture_position.y);";
            source << "}";
        }

        VertexShader::~VertexShader()
        {
        }

        void VertexShader::SetCamera(const entity::Camera *camera)
        {
            _camera = camera;
        }

        void VertexShader::Update()
        {
            _program.GetVariable(MODEL_VARIABLE_NAME).SetMat(_entity->GetModel());
            if (_camera)
            {
                _program.GetVariable(VIEW_VARIABLE_NAME).SetMat(_camera->GetView());
                _program.GetVariable(PROJECTION_VARIABLE_NAME).SetMat(_camera->GetProjection());
            }
        }
    }
}
