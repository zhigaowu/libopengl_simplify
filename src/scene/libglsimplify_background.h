/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_background.h
 *
 *    Description:  the scene background
 *
 *        Version:  1.0
 *        Created:  2024-11-20 15:24:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_SCENE_BACKGROUND_H
#define GL_SIMPLIFY_SCENE_BACKGROUND_H

#include "core/libglsimplify_types.h"

namespace gl_simplify {

    namespace scene {

        class Background : private core::NonCopyable {
        private:
            glm::vec4 _color;

        public:
            Background();
            ~Background();

            void SetColor(const glm::vec4& color);

            void Update();
        };
    }
}

#endif // GL_SIMPLIFY_SCENE_BACKGROUND_H
