
#include "libglsimplify_shader.h"

namespace gl_simplify {

    namespace core {

        GLint Shader::MaxVertexAttributesSupported()
        {
            GLint value = 0;
            glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
            return value;
        }

        Shader::Shader(GLenum shader_type)
            : id(glCreateShader(shader_type))
            , type(shader_type)
            
            , _sources_code()
            , _sources_code_ref()
        {
            _sources_code.reserve(64);
            _sources_code_ref.reserve(64);
        }

        Shader::~Shader()
        {
            glDeleteShader(id);
        }

        Shader &Shader::AddSource(const ShaderSource &source)
        {
            _sources_code.emplace_back(source.Code());
            _sources_code_ref.push_back(_sources_code.back().c_str());

            return *this;
        }

        bool Shader::Compile(GLchar* error, GLsizei error_length)
        {
            glShaderSource(id, static_cast<GLsizei>(_sources_code.size()), _sources_code_ref.data(), nullptr);
            glCompileShader(id);

            int success = 0;
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);

            if(0 != success)
            {
                return true;
            }
            else
            {
                glGetShaderInfoLog(id, error_length, nullptr, error);
                
                return false;
            }
        }
    }
}

