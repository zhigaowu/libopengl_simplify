
#include "libglsimplify_spot_light.h"

namespace gl_simplify {

    namespace light {

        SpotLight::SpotLight(const glm::vec3& position)
            : PointLight(position)

            , _direction(0.0f, -1.0f, 0.0f)

            , _range_inner_angle(23.0f)
            , _range_inner(glm::cos(glm::radians(_range_inner_angle)))
            
            , _range_outer_angle(25.0f)
            , _range_outer(glm::cos(glm::radians(_range_outer_angle)))
        {
        }

        SpotLight::~SpotLight()
        {
        }

        void SpotLight::SetDirection(const glm::vec3 &direction)
        {
            _direction = glm::normalize(direction);
        }

        const glm::vec3 &SpotLight::GetDirection()
        {
            return _direction;
        }

        void SpotLight::SetRangeInner(float range_angle)
        {
            if (range_angle < 90.0f && range_angle > 0.0f)
            {
                if (range_angle > _range_outer_angle)
                {
                    _range_inner_angle = _range_outer_angle;
                    _range_outer_angle = range_angle;
                }
                else
                {
                    _range_inner_angle = range_angle;
                }

                _range_inner = glm::cos(glm::radians(_range_inner_angle));
                _range_outer = glm::cos(glm::radians(_range_outer_angle));
            }
        }

        float SpotLight::GetRangeInner()
        {
            return _range_inner;
        }

        void SpotLight::SetRangeOuter(float range_angle)
        {
            if (range_angle < 90.0f && range_angle > 0.0f)
            {
                if (range_angle < _range_inner_angle)
                {
                    _range_outer_angle = _range_inner_angle;
                    _range_inner_angle = range_angle;
                }
                else
                {
                    _range_outer_angle = range_angle;
                }

                _range_inner = glm::cos(glm::radians(_range_inner_angle));
                _range_outer = glm::cos(glm::radians(_range_outer_angle));
            }
        }

        float SpotLight::GetRangeOuter()
        {
            return _range_outer;
        }
    }
}

