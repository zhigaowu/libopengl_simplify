
#include "libglsimplify_vertex_shader.h"

#include "libglsimplify_program.h"

namespace gl_simplify {

    namespace core {

        GLint VertexShader::MaxVertexAttributesSupported()
        {
            GLint value = 0;
            glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
            return value;
        }

        VertexShader::VertexShader(Program& program)
            : Shader(program, GL_VERTEX_SHADER)
        {
            
        }

        VertexShader::~VertexShader()
        {
        }
    }
}
