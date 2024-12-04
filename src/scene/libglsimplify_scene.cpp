
#include "libglsimplify_scene.h"

#include "model/libglsimplify_phong_model.h"

namespace gl_simplify {

    namespace scene {
        void Scene::updateDirectionalLights()
        {
            _render_model->UpdateDirectionalLight(_directional_light);
        }

        void Scene::destroyDirectionalLights()
        {
            delete _directional_light;
            _directional_light = nullptr;
        }

        void Scene::updatePointLights()
        {
            const GLint light_count = static_cast<GLint>(_point_light_array.size());

            _render_model->UpdatePointLightCount(light_count);
            
            for (GLint i = 0; i < light_count; ++i)
            {
                _render_model->UpdatePointLight(_point_light_array[i], i);
            }
            
        }

        void Scene::destroyPointLights()
        {
            const GLint light_count = static_cast<GLint>(_point_light_array.size());
            
            for (GLint i = 0; i < light_count; ++i)
            {
                delete _point_light_array[i];
                _point_light_array[i] = nullptr;
            }

            _point_light_array.clear();
        }

        void Scene::updateSpotLights()
        {
            const GLint light_count = static_cast<GLint>(_spot_light_array.size());

            _render_model->UpdateSpotLightCount(light_count);
            
            for (GLint i = 0; i < light_count; ++i)
            {
                _render_model->UpdateSpotLight(_spot_light_array[i], i);
            }
        }

        void Scene::destroySpotLights()
        {
            
            const GLint light_count = static_cast<GLint>(_spot_light_array.size());
            
            for (GLint i = 0; i < light_count; ++i)
            {
                delete _spot_light_array[i];
                _spot_light_array[i] = nullptr;
            }

            _spot_light_array.clear();
        }

        Scene::Scene()
            : _background()
            
            , _render_model(new model::PhongModel())

            , _directional_light(new light::DirectionalLight())

            , _point_light_array()
            , _spot_light_array()

            , _entities()
        {
        }

        Scene::~Scene()
        {
        }

        light::DirectionalLight *Scene::GetDirectionalLight()
        {
            return _directional_light;
        }

        light::PointLight* Scene::AddPointLight(const glm::vec3& position)
        {
            light::PointLight* light = new light::PointLight(position);

            _point_light_array.emplace_back(light);

            return light;
        }

        light::PointLight *Scene::GetPointLight(GLint index)
        {
            if (index >= 0 && index < _point_light_array.size())
            {
                return _point_light_array[index];
            }
            return nullptr;
        }

        light::SpotLight* Scene::AddSpotLight(const glm::vec3& position, const glm::vec3& direction)
        {
            light::SpotLight *light = new light::SpotLight(position);

            light->SetDirection(direction);

            _spot_light_array.emplace_back(light);

            return light;
        }

        light::SpotLight *Scene::GetSpotLight(GLint index)
        {
            if (index >= 0 && index < _spot_light_array.size())
            {
                return _spot_light_array[index];
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

        void Scene::Render(entity::Camera* camera)
        {
            _background.Update();

            _render_model->Use();

            _render_model->UpdateCameraView(camera);
            
            updateDirectionalLights();

            updatePointLights();

            updateSpotLights();

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

            destroyDirectionalLights();

            destroyPointLights();

            destroySpotLights();

            delete _render_model;
            _render_model = nullptr;
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

