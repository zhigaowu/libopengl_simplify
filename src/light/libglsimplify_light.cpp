
#include "libglsimplify_light.h"

namespace gl_simplify {

    namespace light {

        Light::Light(const glm::vec4& color, const glm::vec3& position)
            : Entity(position)

            , _color(color)
        {
        }

        Light::~Light()
        {
        }

        void Light::SetColor(const glm::vec4& color)
        {
            _color = color;
        }

        const glm::vec4 &Light::GetColor()
        {
            return _color;
        }

        void Light::Create()
        {
            
        }
    }
}

