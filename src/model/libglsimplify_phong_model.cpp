
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
             * https://learnopengl.com/Lighting/Lighting-maps
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
            _vertex_shader.source << "   TexturePosition = vec2(uv_position.x, uv_position.y);";

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

            _fragment_shader.source << "    sampler2D diffuse;";
            _fragment_shader.source << "    sampler2D specular;";
            _fragment_shader.source << "};";
            
            _fragment_shader.source << "in vec3 NormalDirection;";
            _fragment_shader.source << "in vec2 TexturePosition;";

            _fragment_shader.source << "in vec3 FragmentPosition;";

            _fragment_shader.source << "uniform vec3 camera_position;";

            _fragment_shader.source << "uniform Light light;";
            _fragment_shader.source << "uniform Material material;";
            
            _fragment_shader.source << "void main()";
            _fragment_shader.source << "{";

            // get diffuse/specular map color
            _fragment_shader.source << "   vec4 diffuse_map_color = texture(material.diffuse, TexturePosition);"; // texture(material.diffuse, TexturePosition); vec4(0.0, 0.0, 0.0, 1.0)
            _fragment_shader.source << "   vec4 specular_map_color = texture(material.specular, TexturePosition);"; // texture(material.specular, TexturePosition)

            // calculate ambient color
            _fragment_shader.source << "   vec4 ambient_color = light.ambient * specular_map_color;";

            // calculate diffuse color
            _fragment_shader.source << "   vec3 normalized_normal_direction = normalize(NormalDirection);";
            _fragment_shader.source << "   vec3 normalized_light_direction = normalize(light.position - FragmentPosition);";
            _fragment_shader.source << "   float diffuse_factor = max(dot(normalized_normal_direction, normalized_light_direction), 0.0);";
            _fragment_shader.source << "   vec4 diffuse_color = light.diffuse * diffuse_factor * diffuse_map_color;";
            
            // calculate specular color
            _fragment_shader.source << "   vec3 normalized_camera_direction = normalize(camera_position - FragmentPosition);";
            _fragment_shader.source << "   vec3 normalized_reflect_direction = reflect(-normalized_light_direction, normalized_normal_direction);";
            _fragment_shader.source << "   float specular_factor = pow(max(dot(normalized_camera_direction, normalized_reflect_direction), 0.0), material.shininess);";
            _fragment_shader.source << "   vec4 specular_color = light.specular * specular_factor * specular_map_color;";
            
            // calculate result color
            _fragment_shader.source << "   vec4 result_entity_color = ambient_color + diffuse_color + specular_color;";

            _fragment_shader.source << "   FragColor = result_entity_color;";
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

            GLint diffuse_unit = material->GetDiffuse();
            GLint specular_unit = material->GetSpecular();
            _program.GetVariable("material.diffuse").SetValue(diffuse_unit);
            _program.GetVariable("material.specular").SetValue(specular_unit);
        }

        void PhongModel::Render(entity::Entity* entity)
        {
            _program.GetVariable("model").SetMat(entity->GetModel());
            _program.GetVariable("normal_model").SetMat(entity->GetNormalModel());

            entity->Render();
        }
    }
}
