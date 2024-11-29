
#include "libglsimplify_ambient.h"

namespace gl_simplify {

    namespace scene {

        Ambient::Ambient(const glm::vec4& color, GLfloat strength)
            : _color(color)
            , _strength(strength)

            , _compsite(_strength * _color)
        {
        }

        Ambient::~Ambient()
        {
        }

        void Ambient::SetColor(const glm::vec4 &color)
        {
            _color = color;

            _compsite = _strength * _color;
        }

        void Ambient::SetStrength(GLfloat strength)
        {
            _strength = strength;

            _compsite = _strength * _color;
        }

        Ambient::operator glm::vec4() const {
            return _compsite;
        }
        
    }
}

