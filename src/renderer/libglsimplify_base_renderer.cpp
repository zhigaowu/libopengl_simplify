
#include "libglsimplify_base_renderer.h"

namespace gl_simplify {

    namespace renderer {

        BaseRenderer::BaseRenderer()
            : core::NonCopyable()

            , _program()
            
            , _vertex_shader(GL_VERTEX_SHADER)
            , _fragment_shader(GL_FRAGMENT_SHADER)
        {
        }

        BaseRenderer::~BaseRenderer()
        {
        }

        bool BaseRenderer::Build(GLchar *error, GLsizei error_length)
        {
            return _vertex_shader.Compile(error, error_length) 
                    && _fragment_shader.Compile(error, error_length) 
                    && _program.Attach(_vertex_shader).Attach(_fragment_shader).Link(error, error_length);
        }

        void BaseRenderer::Use()
        {
            _program.Use();
        }

        void BaseRenderer::BindCamera(const camera::BaseCameraPtr &camera)
        {
            _program.GetVariable("view").SetMat(camera->GetView());
            _program.GetVariable("projection").SetMat(camera->GetProjection());
        }

        void BaseRenderer::Render(const entity::BaseEntityPtr &entity)
        {
            _program.GetVariable("model").SetMat(entity->GetModel());

            entity->Render();
        }
    }
}
