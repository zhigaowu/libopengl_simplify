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

#include "libglsimplify_background.h"
#include "libglsimplify_ambient.h"

#include "entity/libglsimplify_camera.h"
#include "model/libglsimplify_render_model.h"

#include "light/libglsimplify_light.h"

#include <map>

namespace gl_simplify {

    namespace scene {

        class Scene : private core::NonCopyable {
        public:
            enum class RenderMode {
                Point = GL_POINT,
                Line = GL_LINE,
                Fill = GL_FILL
            };

        private:
            Background _background;

        private:
            Ambient _ambient;

        private:
            model::RenderModel* _render_model;

        private:
            light::Light* _light;

        private:
            // eneities
            using Entities = std::map<entity::Entity*, entity::Entity*>;
            Entities _entities;

        public:
            Scene();
            virtual ~Scene();

            Background& GetBackground() { return _background; }
            Ambient& GetAmbient() { return _ambient; };

            light::Light* GetLight() { return _light; }

            virtual bool Create(GLchar* error, GLsizei error_length);
            virtual void Render(entity::Camera* camera);
            virtual void Destroy();

            void SetRenderMode(RenderMode render_mode);
            void SetRenderModel(model::RenderModel* render_model);

            void AddEntity(entity::Entity* entity);
            void DeleteEntity(entity::Entity* entity);
        };
    }
}

#endif // GL_SIMPLIFY_SCENE_SCENE_H
