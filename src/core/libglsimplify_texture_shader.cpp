
#include "libglsimplify_texture_shader.h"

#include "libglsimplify_program.h"

namespace gl_simplify {

    namespace core {

        TextureShader::TextureShader(Program& program, GLuint texture_unit)
            : Shader(program, GL_FRAGMENT_SHADER)
            
            , _texture_unit(texture_unit)
            , _texture_buffer()
        {
            source << "out vec4 FragColor;";
            
            source << "in vec2 TexCoord;";
            source << "uniform sampler2D texture_unit;";
            
            source << "void main()";
            source << "{";
            source << "   FragColor = texture(texture_unit, TexCoord);";
            source << "}";
        }

        TextureShader::~TextureShader()
        {
        }

        void TextureShader::SetFile(const std::string& path)
        {
            _texture_buffer.GetTexture().Bind(_texture_unit);
            
            _texture_buffer.GetTexture()
                .SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
                .SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
                .SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                .SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR).UploadImage(path);
                
            _texture_buffer.GetTexture().Unbind();

            _program.Use();
            _program.GetVariable("texture_unit").SetValue(_texture_unit - GL_TEXTURE0);
        }

        void TextureShader::Update()
        {
            _texture_buffer.GetTexture().Bind(_texture_unit);
        }
    }
}
