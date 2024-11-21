
#include "libglsimplify_color_shader.h"

#include "libglsimplify_program.h"

namespace gl_simplify {

    namespace core {

        ColorShader::ColorShader(const glm::vec4& color)
            : Shader(GL_FRAGMENT_SHADER)
            , _color(color)
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

        void ColorShader::Update(Program &program)
        {
            program.GetVariable("input_color").SetVec(_color);
        }
    }
}
