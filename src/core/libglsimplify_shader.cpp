
#include "libglsimplify_shader.h"

#include "libglsimplify_program.h"

namespace gl_simplify {

    namespace core {

        Shader::Shader(GLenum shader_type, const std::string& source_code)
            : id(glCreateShader(shader_type))
            , type(shader_type)

            , source(source_code)
        {
        }

        Shader::~Shader()
        {
            glDeleteShader(id);
        }

        bool Shader::Compile(GLchar* error, GLsizei error_length)
        {
            std::string source_string = source.Source();

            const GLchar* sources[1] = { source_string.c_str() };

            glShaderSource(id, 1, sources, nullptr);
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

        void Shader::Update(Program &program)
        {
        }
    }
}

