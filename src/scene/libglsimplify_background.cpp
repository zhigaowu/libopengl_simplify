
#include "libglsimplify_background.h"

namespace gl_simplify {

    namespace scene {

        Background::Background()
            : _color(0.0, 0.0, 0.0, 1.0)
        {
        }

        Background::~Background()
        {
        }

        void Background::SetColor(const glm::vec4 &color)
        {
            _color = color;
        }

        void Background::Update()
        {
            glClearColor(_color.r, _color.g, _color.b, _color.a);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    }
}

