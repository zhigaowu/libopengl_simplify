
#include "libglsimplify_basic_renderer.h"

namespace gl_simplify {

    namespace renderer::background {

        BasicRenderer::BasicRenderer()
            : renderer::BaseRenderer()

            , _color(0.2f, 0.3f, 0.3f, 1.0f)
        {
            
        }

        BasicRenderer::~BasicRenderer()
        {
        }

        void BasicRenderer::SetColor(const glm::vec4 &color)
        {
            _color = color;
        }

        void BasicRenderer::Clear()
        {
            glClearColor(_color.r, _color.g, _color.b, _color.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void BasicRenderer::Render(const entity::BaseEntityPtr& entity)
        {
        }

    }
}

