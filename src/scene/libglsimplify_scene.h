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

#include "renderer/background/libglsimplify_basic_renderer.h"
#include "renderer/text/libglsimplify_base_text_renderer.h"

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
            camera::BaseCameraPtr _camera;

        private:
            renderer::background::BasicRendererPtr _background;

        private:
            using EntityTypeRenderers = std::vector<renderer::BaseRendererPtr>;
            EntityTypeRenderers _entity_type_renderers;

        private:
            // eneities
            using Entities = std::list<entity::BaseEntityPtr>;
            using EntityTypeGroups = std::vector<Entities>;
            EntityTypeGroups _entity_groups;

        public:
            Scene(int width, int height);
            ~Scene();

            camera::BaseCameraPtr GetCamera() { return _camera; }

            void SetBackground(const renderer::background::BasicRendererPtr& background);
            renderer::background::BasicRendererPtr GetBackground() const { return _background; }

            void SetEntityRenderer(entity::EntityType type, const renderer::BaseRendererPtr& renderer);

            renderer::text::BaseTextRendererPtr GetTextRenderer() const;

            void SetRenderMode(RenderMode render_mode);

            void SetMultipleSampling(bool enabled);

            void enableCullFace(bool enabled);
            void setFrontFace(GLenum mode);
            void setCullFace(GLenum mode);

            bool Create(GLchar* error, GLsizei error_length);
            void Render();
            void Destroy();

            void AddEntity(const entity::BaseEntityPtr& entity);
            void DeleteEntity(const entity::BaseEntityPtr& entity);
        };

        using ScenePtr = std::shared_ptr<Scene>;
    }
}

#define CreateScene(...) CreateWithParameter(gl_simplify::scene::Scene, __VA_ARGS__)

#endif // GL_SIMPLIFY_SCENE_SCENE_H
