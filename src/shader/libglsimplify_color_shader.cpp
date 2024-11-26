
#include "libglsimplify_color_shader.h"

#include "entity/libglsimplify_entity.h"

#include "core/libglsimplify_program.h"

namespace gl_simplify {

    namespace shader {

        ColorShader::ColorShader(entity::Entity* entity)
            : Shader(entity->GetProgram(), GL_FRAGMENT_SHADER)
            , _color(glm::vec4(1.0, 1.0, 1.0, 1.0))
        {
            source << "out vec4 FragColor;";
            source << "";
            source << "uniform vec4 input_color;";
            source << "";
            source << "void main()";
            source << "{";
            source << "   FragColor = input_color;";
            source << "}";
        }

        ColorShader::~ColorShader()
        {
        }

        void ColorShader::SetColor(const glm::vec4 &color)
        {
            _color = color;
        }

        void ColorShader::Update()
        {
            _program.GetVariable("input_color").SetVec(_color);
        }
    }
}
