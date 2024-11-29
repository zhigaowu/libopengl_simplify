
#include "libglsimplify_phong_model.h"

namespace gl_simplify {

    namespace model {

        PhongModel::PhongModel()
            : RenderModel()
        {
            /*
             * shader reference https://learnopengl.com/Lighting/Basic-Lighting
            */

            // initialize vertext shader source
            _vertex_shader.source << "layout (location = 0) in vec3 model_position;";
            _vertex_shader.source << "layout (location = 1) in vec3 normal_direction;";
            _vertex_shader.source << "layout (location = 2) in vec2 uv_position;";

            _vertex_shader.source << "out vec3 NormalDirection;";
            _vertex_shader.source << "out vec2 TexturePosition;";

            _vertex_shader.source << "out vec3 FragmentPosition;";

            _vertex_shader.source << "uniform mat4 model;";
            _vertex_shader.source << "uniform mat3 normal_model;";

            _vertex_shader.source << "uniform mat4 view;";
            _vertex_shader.source << "uniform mat4 projection;";

            _vertex_shader.source << "void main()";
            _vertex_shader.source << "{" ;
            _vertex_shader.source << "   NormalDirection = normal_model * normal_direction;";
            _vertex_shader.source << "   TexturePosition = vec2(uv_position.x, 1.0 - uv_position.y);";

            _vertex_shader.source << "   vec4 fragment_position = model * vec4(model_position, 1.0);";
            _vertex_shader.source << "   FragmentPosition = fragment_position.xyz;";
            _vertex_shader.source << "   gl_Position = projection * view * fragment_position;";
            _vertex_shader.source << "}";

            // initialize fragment shader source
            _fragment_shader.source << "out vec4 FragColor;";
            
            _fragment_shader.source << "in vec3 NormalDirection;";
            _fragment_shader.source << "in vec2 TexturePosition;";

            _fragment_shader.source << "in vec3 FragmentPosition;";

            _fragment_shader.source << "uniform sampler2D texture_unit;";

            _fragment_shader.source << "uniform vec4 entity_color;";

            _fragment_shader.source << "uniform vec4 ambient_color;";

            _fragment_shader.source << "uniform vec3 light_position;";
            _fragment_shader.source << "uniform vec4 light_color;";

            _fragment_shader.source << "uniform vec3 camera_position;";

            _fragment_shader.source << "uniform float specular_strength;";
            _fragment_shader.source << "uniform uint specular_shininess;";
            
            _fragment_shader.source << "void main()";
            _fragment_shader.source << "{";

            // calculate diffuse color
            _fragment_shader.source << "   vec3 normalized_normal_direction = normalize(NormalDirection);";
            _fragment_shader.source << "   vec3 normalized_light_direction = normalize(light_position - FragmentPosition);";
            _fragment_shader.source << "   vec4 diffuse_color = max(dot(normalized_normal_direction, normalized_light_direction), 0.0) * light_color;";
            
            // calculate specular color
            _fragment_shader.source << "   vec3 normalized_camera_direction = normalize(camera_position - FragmentPosition);";
            _fragment_shader.source << "   vec3 normalized_reflect_direction = normalize(reflect(-normalized_light_direction, normalized_normal_direction));";
            _fragment_shader.source << "   vec4 specular_color = specular_strength * pow(max(dot(normalized_camera_direction, normalized_reflect_direction), 0.0), specular_shininess) * light_color;";
            
            // calculate result color
            _fragment_shader.source << "   vec4 result_entity_color = (ambient_color + diffuse_color + specular_color) * entity_color;";

            _fragment_shader.source << "   FragColor = texture(texture_unit, TexturePosition) * result_entity_color;";
            _fragment_shader.source << "}";
        }

        PhongModel::~PhongModel()
        {
        }

        void PhongModel::UpdateCameraView(entity::Camera* camera)
        {
            _program.GetVariable("view").SetMat(camera->GetView());
            _program.GetVariable("projection").SetMat(camera->GetProjection());

            _program.GetVariable("camera_position").SetVec(camera->GetPosition());
        }

        void PhongModel::UpdateAmbient(const glm::vec4 &ambient)
        {
            _program.GetVariable("ambient_color").SetVec(ambient);
        }

        void PhongModel::UpdateLight(light::Light *light)
        {
            _program.GetVariable("light_color").SetVec(light->GetColor());
            _program.GetVariable("light_position").SetVec(light->GetPosition());
        }

        void PhongModel::Render(entity::Entity* entity)
        {
            _program.GetVariable("model").SetMat(entity->GetModel());
            _program.GetVariable("normal_model").SetMat(entity->GetNormalModel());

            material::SharedMaterial& material = entity->GetMaterial();
            _program.GetVariable("entity_color").SetVec(material->GetColor());
            _program.GetVariable("specular_strength").SetValue(material->GetSpecularStrength());
            _program.GetVariable("specular_shininess").SetValue(material->GetSpecularShininess());

            entity->Render();
        }
    }
}
