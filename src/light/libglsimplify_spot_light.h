/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_spot_light.h
 *
 *    Description:  spot light object
 * 
 *        Version:  1.0
 *        Created:  2024-12-03 17:10:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_LIGHT_SPOT_LIGHT_H
#define GL_SIMPLIFY_LIGHT_SPOT_LIGHT_H

#include "libglsimplify_point_light.h"

namespace gl_simplify {

    namespace light {

        /*
         * reference: https://learnopengl.com/Lighting/Light-casters
        */
        class SpotLight : public PointLight {
        protected:
            glm::vec3 _direction;

        protected:
            float _range_inner_angle;
            float _range_inner;

            float _range_outer_angle;
            float _range_outer;

        public:
            explicit SpotLight(const glm::vec3& position = glm::vec3(8.0, 8.0, 8.0));
            ~SpotLight();

            void SetDirection(const glm::vec3& direction);
            const glm::vec3& GetDirection();

            void SetRangeInner(float range_angle);
            float GetRangeInner();

            void SetRangeOuter(float range_angle);
            float GetRangeOuter();
        };

        using SpotLightPtr = std::shared_ptr<SpotLight>;
        using SpotLights = std::vector<SpotLightPtr>;
    }
}

#endif // GL_SIMPLIFY_LIGHT_SPOT_LIGHT_H
