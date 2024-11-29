
#include "libglsimplify_light.h"

namespace gl_simplify {

    namespace light {

        Light::Light(const glm::vec3& position)
            : Entity(position)

            , _ambient(1.0f, 1.0f, 1.0f, 1.0f)
            , _diffuse(1.0f, 1.0f, 1.0f, 1.0f)
            , _specular(1.0f, 1.0f, 1.0f, 1.0f)
        {
        }

        Light::~Light()
        {
        }

        void Light::SetAmbient(const glm::vec4& ambient)
        {
            _ambient = ambient;
        }

        const glm::vec4 &Light::GetAmbient()
        {
            return _ambient;
        }

        void Light::SetDiffuse(const glm::vec4& diffuse)
        {
            _diffuse = diffuse;
        }

        const glm::vec4 &Light::GetDiffuse()
        {
            return _diffuse;
        }

        void Light::SetSpecular(const glm::vec4& specular)
        {
            _specular = specular;
        }

        const glm::vec4 &Light::GetSpecular()
        {
            return _specular;
        }

        void Light::Create()
        {
            
        }
    }
}

