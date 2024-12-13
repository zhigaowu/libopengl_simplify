/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_directional_light.h
 *
 *    Description:  directional light object
 * 
 *        Version:  1.0
 *        Created:  2024-12-03 17:10:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_LIGHT_DIRECTIONAL_LIGHT_H
#define GL_SIMPLIFY_LIGHT_DIRECTIONAL_LIGHT_H

#include "libglsimplify_light.h"

namespace gl_simplify {

    namespace light {

        /*
         * reference: https://learnopengl.com/Lighting/Light-casters
        */
        class DirectionalLight : public Light {
        protected:
            glm::vec3 _direction;

        public:
            explicit DirectionalLight(const glm::vec3& position = glm::vec3(8.0, 8.0, 8.0));
            ~DirectionalLight();

            void SetDirection(const glm::vec3& direction);
            const glm::vec3& GetDirection();
        };

        using DirectionalLightPtr = std::shared_ptr<DirectionalLight>;
        using DirectionalLights = std::vector<DirectionalLightPtr>;
    }
}

#endif // GL_SIMPLIFY_LIGHT_DIRECTIONAL_LIGHT_H
