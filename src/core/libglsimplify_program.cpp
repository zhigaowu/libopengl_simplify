
#include "libglsimplify_program.h"

namespace gl_simplify {

    namespace core {

        Program::Program()
            : _program_id(glCreateProgram())
        {
        }

        Program::~Program()
        {
            glDeleteProgram(_program_id);
        }

        Program &Program::Attach(const Shader &shader)
        {
            glAttachShader(_program_id, shader.id);

            return *this;
        }

        bool Program::Link(GLchar* error, GLsizei error_length)
        {
            glLinkProgram(_program_id);

            int success = 0;
            glGetProgramiv(_program_id, GL_LINK_STATUS, &success);

            if(0 != success)
            {
                return true;
            }
            else
            {
                glGetProgramInfoLog(_program_id, error_length, nullptr, error);
                
                return false;
            }
        }

        Program &Program::Use()
        {
            glUseProgram(_program_id);

            return *this;
        }

        Program &Program::Use(const ProgramConfigurer &program_configuer)
        {
            glUseProgram(_program_id);

            program_configuer(*this);

            return *this;
        }

        Program::Variable Program::GetVariable(const std::string &vavriable_name)
        {
            return Variable(glGetUniformLocation(_program_id, vavriable_name.c_str()));
        }
    }
}

