/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_light.h
 *
 *    Description:  light object
 * 
 *        Version:  1.0
 *        Created:  2024-11-28 11:31:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_LIGHT_LIGHT_H
#define GL_SIMPLIFY_LIGHT_LIGHT_H

#include "entity/libglsimplify_entity.h"

namespace gl_simplify {

    namespace light {

        class Light : public entity::Entity {
        protected:
            glm::vec4 _color;

        public:
            explicit Light(const glm::vec4& color, const glm::vec3& position = glm::vec3(8.0, 8.0, 8.0));
            virtual ~Light();

            void SetColor(const glm::vec4& color);
            const glm::vec4& GetColor();

            void Create() override;
        };
    }
}

#endif // GL_SIMPLIFY_LIGHT_LIGHT_H
