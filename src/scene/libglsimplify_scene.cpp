
#include "libglsimplify_scene.h"

namespace gl_simplify {

    namespace scene {

        Scene::Scene()
            : _background()

            , _entities()
        {
        }

        Scene::~Scene()
        {
        }

        bool Scene::Create(GLchar *error, GLsizei error_length)
        {
            // -------- default render option ---------
            glEnable(GL_DEPTH_TEST);

            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CCW);
            glCullFace(GL_BACK);

            SetRenderMode(RenderMode::Fill);

            // -------- other initialization ---------
            (void)error;
            (void)error_length;

            return true;
        }

        void Scene::SetRenderMode(RenderMode render_mode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLint>(render_mode));
        }

        void Scene::AddEntity(entity::Entity* entity)
        {
            if (entity)
            {
                _entities.emplace(entity, entity);
            }
        }

        void Scene::DeleteEntity(entity::Entity *entity)
        {
            _entities.erase(entity);
        }

        void Scene::Render(entity::Camera* camera)
        {
            _background.Update();

            for (Entities::iterator it = _entities.begin(); it != _entities.end(); ++it)
            {
                it->second->Render(camera);
            }
        }

        void Scene::Destroy()
        {
            for (Entities::iterator it = _entities.begin(); it != _entities.end(); ++it)
            {
                it->second->Destroy();

                delete it->second;
            }
            
            _entities.clear();
        }
    }
}

