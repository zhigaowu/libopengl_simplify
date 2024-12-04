
#include "libglsimplify_point_light.h"

namespace gl_simplify {

    namespace light {

        PointLight::PointLight(const glm::vec3& position)
            : Light(position)

            , _attenuation_Kc(1.0f)
            , _attenuation_Kl(0.09f)
            , _attenuation_Kq(0.032f)
        {
        }

        PointLight::~PointLight()
        {
        }

        void PointLight::SetAttenuationKc(float Kc)
        {
            _attenuation_Kc = Kc;
        }

        float PointLight::GetAttenuationKc()
        {
            return _attenuation_Kc;
        }

        void PointLight::SetAttenuationKl(float Kl)
        {
            _attenuation_Kl = Kl;
        }

        float PointLight::GetAttenuationKl()
        {
            return _attenuation_Kl;
        }

        void PointLight::SetAttenuationKq(float Kq)
        {
            _attenuation_Kq = Kq;
        }

        float PointLight::GetAttenuationKq()
        {
            return _attenuation_Kq;
        }
    }
}

