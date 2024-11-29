
#include "libglsimplify_phong_model.h"

namespace gl_simplify {

    namespace model {

        PhongModel::PhongModel()
            : RenderModel()
        {
            /*
             * shader reference:
             * https://learnopengl.com/Lighting/Basic-Lighting
             * https://learnopengl.com/Lighting/Materials
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

            // light definition
            _fragment_shader.source << "struct Light {";
            _fragment_shader.source << "    vec3 position;";

            _fragment_shader.source << "    vec4 ambient;";
            _fragment_shader.source << "    vec4 diffuse;";
            _fragment_shader.source << "    vec4 specular;";
            _fragment_shader.source << "};";

            // material definition
            _fragment_shader.source << "struct Material {";
            _fragment_shader.source << "    float shininess;";

            _fragment_shader.source << "    vec4 ambient;";
            _fragment_shader.source << "    vec4 diffuse;";
            _fragment_shader.source << "    vec4 specular;";
            _fragment_shader.source << "};";
            
            _fragment_shader.source << "in vec3 NormalDirection;";
            _fragment_shader.source << "in vec2 TexturePosition;";

            _fragment_shader.source << "in vec3 FragmentPosition;";

            _fragment_shader.source << "uniform sampler2D texture_unit;";

            _fragment_shader.source << "uniform vec3 camera_position;";

            _fragment_shader.source << "uniform Light light;";
            _fragment_shader.source << "uniform Material material;";
            
            _fragment_shader.source << "void main()";
            _fragment_shader.source << "{";

            // calculate ambient color
            _fragment_shader.source << "   vec4 ambient_color = light.ambient * material.ambient;";

            // calculate diffuse color
            _fragment_shader.source << "   vec3 normalized_normal_direction = normalize(NormalDirection);";
            _fragment_shader.source << "   vec3 normalized_light_direction = normalize(light.position - FragmentPosition);";
            _fragment_shader.source << "   vec4 diffuse_color = light.diffuse * (max(dot(normalized_normal_direction, normalized_light_direction), 0.0) * material.diffuse);";
            
            // calculate specular color
            _fragment_shader.source << "   vec3 normalized_camera_direction = normalize(camera_position - FragmentPosition);";
            _fragment_shader.source << "   vec3 normalized_reflect_direction = normalize(reflect(-normalized_light_direction, normalized_normal_direction));";
            _fragment_shader.source << "   vec4 specular_color = light.specular * (pow(max(dot(normalized_camera_direction, normalized_reflect_direction), 0.0), material.shininess) * material.specular);";
            
            // calculate result color
            _fragment_shader.source << "   vec4 result_entity_color = ambient_color + diffuse_color + specular_color;";

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

        void PhongModel::UpdateLight(light::Light *light)
        {
            _program.GetVariable("light.position").SetVec(light->GetPosition());

            _program.GetVariable("light.ambient").SetVec(light->GetAmbient());
            _program.GetVariable("light.diffuse").SetVec(light->GetDiffuse());
            _program.GetVariable("light.specular").SetVec(light->GetSpecular());
        }

        void PhongModel::UpdateMaterial(material::SharedMaterial material)
        {
            _program.GetVariable("material.shininess").SetValue(material->GetShininess());

            _program.GetVariable("material.ambient").SetVec(material->GetAmbient());
            _program.GetVariable("material.diffuse").SetVec(material->GetDiffuse());
            _program.GetVariable("material.specular").SetVec(material->GetSpecular());
        }

        void PhongModel::Render(entity::Entity* entity)
        {
            _program.GetVariable("model").SetMat(entity->GetModel());
            _program.GetVariable("normal_model").SetMat(entity->GetNormalModel());

            entity->Render();
        }
    }
}
