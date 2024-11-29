/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_ambient.h
 *
 *    Description:  the scene ambient
 *
 *        Version:  1.0
 *        Created:  2024-11-28 16:33:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_SCENE_AMBIENT_H
#define GL_SIMPLIFY_SCENE_AMBIENT_H

#include "core/libglsimplify_types.h"

namespace gl_simplify {

    namespace scene {

        class Ambient : private core::NonCopyable {
        private:
            glm::vec4 _color;
            GLfloat _strength;

        private:
            glm::vec4 _compsite;

        public:
            explicit Ambient(const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), GLfloat strength = 0.2f);
            ~Ambient();

            void SetColor(const glm::vec4& color);
            void SetStrength(GLfloat strength);

            operator glm::vec4() const;
        };
    }
}

#endif // GL_SIMPLIFY_SCENE_AMBIENT_H
