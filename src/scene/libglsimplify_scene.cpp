
#include "libglsimplify_scene.h"

#include "model/libglsimplify_phong_model.h"

namespace gl_simplify {

    namespace scene {

        Scene::Scene()
            : _background()
            
            , _render_model(new model::PhongModel())

            , _light(new light::Light())

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

            return _render_model->Build(error, error_length);
        }

        void Scene::Render(entity::Camera* camera)
        {
            _background.Update();

            _render_model->Use();

            _render_model->UpdateCameraView(camera);
            
            _render_model->UpdateLight(_light);

            for (Entities::iterator it = _entities.begin(); it != _entities.end(); ++it)
            {
                _render_model->UpdateMaterial(it->second->GetMaterial());
                
                _render_model->Render(it->second);
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

            delete _render_model;
            _render_model = nullptr;

            delete _light;
            _light = nullptr;
        }

        void Scene::SetRenderMode(RenderMode render_mode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLint>(render_mode));
        }

        void Scene::SetRenderModel(model::RenderModel *render_model)
        {
            if (render_model)
            {
                delete _render_model;
                _render_model = render_model;
            }
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
    }
}

