/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_point_light.h
 *
 *    Description:  point light object
 * 
 *        Version:  1.0
 *        Created:  2024-12-03 17:10:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_LIGHT_POINT_LIGHT_H
#define GL_SIMPLIFY_LIGHT_POINT_LIGHT_H

#include "libglsimplify_light.h"

namespace gl_simplify {

    namespace light {

        /*
         * reference: https://learnopengl.com/Lighting/Light-casters
        */
        class PointLight : public Light {
        protected:
            float _attenuation_Kc;
            float _attenuation_Kl;
            float _attenuation_Kq;

        public:
            explicit PointLight(const glm::vec3& position = glm::vec3(8.0, 8.0, 8.0));
            ~PointLight();

            void SetAttenuationKc(float kc);
            float GetAttenuationKc();

            void SetAttenuationKl(float kl);
            float GetAttenuationKl();

            void SetAttenuationKq(float kq);
            float GetAttenuationKq();
        };

        using PointLightPtr = std::shared_ptr<PointLight>;
        using PointLights = std::vector<PointLightPtr>;
    }
}

#define CreatePointLight() CreateDefaultEntity(gl_simplify::light::PointLight)

#endif // GL_SIMPLIFY_LIGHT_POINT_LIGHT_H
