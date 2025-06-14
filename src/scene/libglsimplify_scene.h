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

#include "entity/libglsimplify_camera.h"

#include "light/libglsimplify_directional_light.h"
#include "light/libglsimplify_spot_light.h"

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
            entity::CameraPtr _camera;

        private:
            Background _background;

        private:
            render::RenderModelPtr _render_model;

        private:
            light::DirectionalLightPtr _directional_light;

        private:
            light::PointLights _point_lights;

        private:
            light::SpotLights _spot_lights;

        private:
            // eneities
            using Entities = std::map<entity::Entity*, entity::EntityPtr>;
            Entities _entities;

        public:
            Scene();
            virtual ~Scene();

            entity::CameraPtr GetCamera() { return _camera; }

            Background& GetBackground() { return _background; }

            light::DirectionalLightPtr GetDirectionalLight();

            light::PointLightPtr AddPointLight(const glm::vec3& position);
            light::PointLightPtr GetPointLight(GLint index);

            light::SpotLightPtr AddSpotLight(const glm::vec3& position, const glm::vec3& direction = glm::vec3(0.0f, -1.0f, 0.0f));
            light::SpotLightPtr GetSpotLight(GLint index);

            virtual bool Create(int width, int height, GLchar* error, GLsizei error_length);
            virtual void Render();
            virtual void Destroy();

            void SetRenderMode(RenderMode render_mode);
            void SetRenderModel(const render::RenderModelPtr& render_model);

            void SetMultipleSampling(bool enabled);

            void AddEntity(const entity::EntityPtr& entity);
            void DeleteEntity(const entity::EntityPtr& entity);
        };

        using ScenePtr = std::shared_ptr<Scene>;
    }
}

#endif // GL_SIMPLIFY_SCENE_SCENE_H
