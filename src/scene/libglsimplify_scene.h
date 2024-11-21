/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_scene.h
 *
 *    Description:  the scene that manage all items in it
 *
 *        Version:  1.0
 *        Created:  2024-11-19 15:00:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_SCENE_SCENE_H
#define GL_SIMPLIFY_SCENE_SCENE_H

#include "entity/libglsimplify_camera.h"

#include "libglsimplify_background.h"

#include <map>

namespace gl_simplify {

    namespace scene {

        class Scene : private core::NonCopyable {
        private:
            Background _background;

        private:
            // eneities
            using Entities = std::map<entity::Entity*, entity::Entity*>;
            Entities _entities;

        public:
            Scene();
            ~Scene();

            Background& GetBackground() { return _background; }

            bool Create(GLchar* error, GLsizei error_length);

            void AddEntity(entity::Entity* entity);
            void DestroyEntity(entity::Entity* entity);

            void Render(entity::Camera* camera);

            void Destroy();
        };
    }
}

#endif // GL_SIMPLIFY_SCENE_SCENE_H
