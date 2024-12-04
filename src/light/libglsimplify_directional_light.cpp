
#include "libglsimplify_directional_light.h"

namespace gl_simplify {

    namespace light {

        DirectionalLight::DirectionalLight(const glm::vec3& position)
            : Light(position)
            , _direction(0.0f, -1.0f, 0.0f)
        {
        }

        DirectionalLight::~DirectionalLight()
        {
        }

        void DirectionalLight::SetDirection(const glm::vec3 &direction)
        {
            _direction = glm::normalize(direction);
        }
        
        const glm::vec3 &DirectionalLight::GetDirection()
        {
            return _direction;
        }
    }
}

