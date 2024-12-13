
#include "libglsimplify_render_shader.h"

namespace gl_simplify {

    namespace render {

        RenderShader::RenderShader()
            : core::NonCopyable()

            , _program()
            
            , _vertex_shader(GL_VERTEX_SHADER)
            , _fragment_shader(GL_FRAGMENT_SHADER)
        {
        }

        RenderShader::~RenderShader()
        {
        }

        bool RenderShader::Build(GLchar *error, GLsizei error_length)
        {
            return _vertex_shader.Compile(error, error_length) 
                    && _fragment_shader.Compile(error, error_length) 
                    && _program.Attach(_vertex_shader).Attach(_fragment_shader).Link(error, error_length);
        }

        void RenderShader::Use()
        {
            _program.Use();
        }

    }
}
