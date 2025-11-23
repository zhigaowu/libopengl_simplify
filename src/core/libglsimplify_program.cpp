
#include "libglsimplify_program.h"

namespace gl_simplify {

    namespace core {

        Program::Program()
            : _gl_program_id(glCreateProgram())
        {
        }

        Program::~Program()
        {
            glDeleteProgram(_gl_program_id);
        }

        Program &Program::Attach(const Shader &shader)
        {
            glAttachShader(_gl_program_id, shader.id);

            return *this;
        }

        bool Program::Link(GLchar* error, GLsizei error_length)
        {
            glLinkProgram(_gl_program_id);

            int success = 0;
            glGetProgramiv(_gl_program_id, GL_LINK_STATUS, &success);

            if(0 != success)
            {
                return true;
            }
            else
            {
                glGetProgramInfoLog(_gl_program_id, error_length, nullptr, error);
                
                return false;
            }
        }

        Program &Program::Use()
        {
            glUseProgram(_gl_program_id);

            return *this;
        }

        Program::Variable Program::GetVariable(const std::string &vavriable_name)
        {
            return Variable(glGetUniformLocation(_gl_program_id, vavriable_name.c_str()));
        }
    }
}

