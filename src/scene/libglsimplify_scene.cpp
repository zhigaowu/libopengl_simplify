
#include "libglsimplify_scene.h"

#include "camera/libglsimplify_default_camera.h"

#include "renderer/background/libglsimplify_basic_renderer.h"
#include "renderer/foreground/libglsimplify_basic_renderer.h"

namespace gl_simplify {

    namespace scene {

        Scene::Scene(int width, int height)
            : core::NonCopyable()
            
            , _camera(CreateDefaultCamera((float)width / (float)height))

            , _background(CreateBasicBackgroundRenderer())
            
            , _entity_type_renderers{CreateBasicForegroundRenderer(), nullptr}

            , _entity_groups(static_cast<size_t>(entity::EntityType::Count))
        {
        }

        Scene::~Scene()
        {
        }

        void Scene::SetBackground(const renderer::background::BasicRendererPtr &background)
        {
            _background = background;
        }

        void Scene::SetEntityRenderer(entity::EntityType type, const renderer::BaseRendererPtr &renderer)
        {
            if (type != entity::EntityType::Count && renderer)
            {
                _entity_type_renderers[static_cast<size_t>(type)] = renderer;
            }
        }

        void Scene::SetRenderMode(RenderMode render_mode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLint>(render_mode));
        }

        void Scene::SetMultipleSampling(bool enabled)
        {
            if (enabled)
            {
                glEnable(GL_MULTISAMPLE);
            }
            else
            {
                glDisable(GL_MULTISAMPLE);
            }
        }

        void Scene::enableCullFace(bool enabled)
        {
            if (enabled)
            {
                glEnable(GL_CULL_FACE);
            }
            else
            {
                glDisable(GL_CULL_FACE);
            }
        }

        void Scene::setFrontFace(GLenum mode)
        {
            glFrontFace(mode);
        }

        void Scene::setCullFace(GLenum mode)
        {
            glCullFace(mode);
        }

        bool Scene::Create(GLchar *error, GLsizei error_length)
        {
            if (!_background || !_background->Build(error, error_length))
            {
                return false;
            }

            for (renderer::BaseRendererPtr& renderer : _entity_type_renderers)
            {
                if (renderer)
                {
                    if (!renderer->Build(error, error_length))
                    {
                        return false;
                    }
                }
            }

            // -------- default render option ---------
            glEnable(GL_DEPTH_TEST);

            enableCullFace(true);
            setFrontFace(GL_CCW);
            setCullFace(GL_BACK);

            SetRenderMode(RenderMode::Fill);
            SetMultipleSampling(true);

            return true;
        }

        void Scene::Render()
        {
            // clear background
            _background->Clear();

            for (size_t i = 0; i < _entity_type_renderers.size(); ++i)
            {
                renderer::BaseRendererPtr& renderer = _entity_type_renderers[i];
                if (renderer)
                {
                    renderer->Use();
                    renderer->BindCamera(_camera);

                    const Entities& entities = _entity_groups[i];
                    for (const entity::BaseEntityPtr& entity : entities)
                    {
                        renderer->Render(entity);
                    }
                }
            }

            // render background
            _background->Use();
            _background->BindCamera(_camera);
            _background->Render(nullptr);
        }

        void Scene::Destroy()
        {
            _entity_type_renderers.clear();

            _entity_groups.clear();
        }

        void Scene::AddEntity(const entity::BaseEntityPtr& entity)
        {
            if (entity)
            {
                Entities& entities = _entity_groups[static_cast<size_t>(entity->GetType())];

                if (std::find_if(entities.begin(), entities.end(), [&entity](const entity::BaseEntityPtr& e) { return e.get() == entity.get(); }) == entities.end())
                {
                    entities.push_back(entity);
                }
            }
        }

        void Scene::DeleteEntity(const entity::BaseEntityPtr& entity)
        {
            if (entity)
            {
                Entities& entities = _entity_groups[static_cast<size_t>(entity->GetType())];

                Entities::iterator it = std::find_if(entities.begin(), entities.end(), [&entity](const entity::BaseEntityPtr& e) { return e.get() == entity.get(); });
                if (it != entities.end())
                {
                    entities.erase(it);
                }
            }
        }
    }
}

