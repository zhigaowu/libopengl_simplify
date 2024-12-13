
#include "libglsimplify_scene.h"

#include "model/libglsimplify_phong_model.h"

namespace gl_simplify {

    namespace scene {

        Scene::Scene()
            : _background()
            
            , _render_model(std::make_shared<model::PhongModel>())

            , _directional_light(std::make_shared<light::DirectionalLight>())

            , _point_lights()
            , _spot_lights()

            , _entities()
        {
        }

        Scene::~Scene()
        {
        }

        light::DirectionalLightPtr Scene::GetDirectionalLight()
        {
            return _directional_light;
        }

        light::PointLightPtr Scene::AddPointLight(const glm::vec3& position)
        {
            light::PointLightPtr light = std::make_shared<light::PointLight>(position);

            _point_lights.emplace_back(light);

            return light;
        }

        light::PointLightPtr Scene::GetPointLight(GLint index)
        {
            if (index >= 0 && index < _point_lights.size())
            {
                return _point_lights[index];
            }
            return nullptr;
        }

        light::SpotLightPtr Scene::AddSpotLight(const glm::vec3& position, const glm::vec3& direction)
        {
            light::SpotLightPtr light = std::make_shared<light::SpotLight>(position);

            light->SetDirection(direction);

            _spot_lights.emplace_back(light);

            return light;
        }

        light::SpotLightPtr Scene::GetSpotLight(GLint index)
        {
            if (index >= 0 && index < _spot_lights.size())
            {
                return _spot_lights[index];
            }
            return nullptr;
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

        void Scene::Render(const entity::CameraPtr& camera)
        {
            // clear background
            _background.Clear();

            // render entities in the scene
            _render_model->Use();
            _render_model->UpdateCameraView(camera);
            _render_model->UpdateDirectionalLight(_directional_light);
            _render_model->UpdatePointLights(_point_lights);
            _render_model->UpdateSpotLights(_spot_lights);

            for (Entities::iterator it = _entities.begin(); it != _entities.end(); ++it)
            {
                entity::EntityPtr& entity = it->second;

                _render_model->UpdateEntity(entity);
                
                entity->Render();
            }

            // render background
            _background.Use();
            _background.UpdateCameraView(camera);
            _background.UpdateDirectionalLight(_directional_light);
            _background.UpdatePointLights(_point_lights);
            _background.UpdateSpotLights(_spot_lights);
            _background.Render();
        }

        void Scene::Destroy()
        {
            _entities.clear();

            _point_lights.clear();
            _spot_lights.clear();
        }

        void Scene::SetRenderMode(RenderMode render_mode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLint>(render_mode));
        }

        void Scene::SetRenderModel(const model::RenderModelPtr& render_model)
        {
            if (render_model)
            {
                _render_model = render_model;
            }
        }

        void Scene::AddEntity(const entity::EntityPtr& entity)
        {
            if (entity)
            {
                _entities.emplace(entity.get(), entity);
            }
        }

        void Scene::DeleteEntity(const entity::EntityPtr& entity)
        {
            _entities.erase(entity.get());
        }
    }
}

