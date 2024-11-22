
#include "libglsimplify_color_shader.h"

#include "libglsimplify_program.h"

namespace gl_simplify {

    namespace core {

        ColorShader::ColorShader(Program& program)
            : Shader(program, GL_FRAGMENT_SHADER)
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
