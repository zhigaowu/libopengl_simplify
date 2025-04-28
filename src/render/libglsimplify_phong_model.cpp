
#include "libglsimplify_phong_model.h"

namespace gl_simplify {

    namespace render {

        static constexpr const GLint Max_Point_Light_Size = 16;
        static constexpr const GLint Max_Spot_Light_Size = 16;

        static class LightNameManager {
        public:
            struct PointLightPropertyName {
                std::string ambient;
                std::string diffuse;
                std::string specular;

                std::string position;

                std::string kc;
                std::string kl;
                std::string kq;
            };

            struct SpotLightPropertyName : public PointLightPropertyName {
                std::string direction;
                std::string range_inner;
                std::string range_outer;
            };

        private:
            std::vector<PointLightPropertyName> _point_light_property_name_list;
            std::vector<SpotLightPropertyName> _spot_light_property_name_list;

        public:
            LightNameManager()
                : _point_light_property_name_list(Max_Point_Light_Size)
                , _spot_light_property_name_list(Max_Spot_Light_Size)
            {
                static std::string point_name_base("point_light[");

                for (GLint p = 0; p < Max_Point_Light_Size; ++p)
                {
                    std::string index = std::to_string(p);

                    PointLightPropertyName& property_name = _point_light_property_name_list[p];

                    property_name.ambient= point_name_base + index + "].ambient";
                    property_name.diffuse= point_name_base + index + "].diffuse";
                    property_name.specular= point_name_base + index + "].specular";

                    property_name.position= point_name_base + index + "].position";

                    property_name.kc= point_name_base + index + "].kc";
                    property_name.kl= point_name_base + index + "].kl";
                    property_name.kq= point_name_base + index + "].kq";
                }
                
                static std::string spot_name_base("spot_light[");

                for (GLint s = 0; s < Max_Spot_Light_Size; ++s)
                {
                    std::string index = std::to_string(s);

                    SpotLightPropertyName& property_name = _spot_light_property_name_list[s];

                    property_name.ambient= spot_name_base + index + "].ambient";
                    property_name.diffuse= spot_name_base + index + "].diffuse";
                    property_name.specular= spot_name_base + index + "].specular";

                    property_name.position= spot_name_base + index + "].position";

                    property_name.kc= spot_name_base + index + "].kc";
                    property_name.kl= spot_name_base + index + "].kl";
                    property_name.kq= spot_name_base + index + "].kq";

                    property_name.direction= spot_name_base + index + "].direction";
                    property_name.range_inner= spot_name_base + index + "].range_inner";
                    property_name.range_outer= spot_name_base + index + "].range_outer";
                }
            }

            const PointLightPropertyName& GetPointLightPropertyName(GLint index)
            {
                return _point_light_property_name_list[index];
            }

            const SpotLightPropertyName& GetSpotLightPropertyName(GLint index)
            {
                return _spot_light_property_name_list[index];
            }

            ~LightNameManager()
            {

            }
        } lightNameManager;

        PhongModel::PhongModel()
            : RenderModel()
        {
            /*
             * shader reference:
             * https://learnopengl.com/Lighting/Basic-Lighting
             * https://learnopengl.com/Lighting/Materials
             * https://learnopengl.com/Lighting/Lighting-maps
             * https://learnopengl.com/Lighting/Multiple-lights
             */

            // initialize vertext shader source
            _vertex_shader.source << "layout (location = 0) in vec3 fragment_local_position;";
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
            _vertex_shader.source << "    NormalDirection = normal_model * normal_direction;";
            _vertex_shader.source << "    TexturePosition = vec2(uv_position.x, uv_position.y);";

            _vertex_shader.source << "    vec4 fragment_position = model * vec4(fragment_local_position, 1.0);";
            _vertex_shader.source << "    FragmentPosition = fragment_position.xyz;";
            _vertex_shader.source << "    gl_Position = projection * view * fragment_position;";
            _vertex_shader.source << "}";

            // initialize fragment shader source
            _fragment_shader.source << "out vec4 FragColor;";

            // material definition
            _fragment_shader.source << "struct Material {";
            _fragment_shader.source << "    sampler2D diffuse;";
            _fragment_shader.source << "    sampler2D specular;";

            _fragment_shader.source << "    float shininess;";
            _fragment_shader.source << "};";

            // directional light definition
            _fragment_shader.source << "struct DirectionalLight {";
            _fragment_shader.source << "    vec4 ambient;";
            _fragment_shader.source << "    vec4 diffuse;";
            _fragment_shader.source << "    vec4 specular;";

            _fragment_shader.source << "    vec3 direction;";
            _fragment_shader.source << "};";

            // point light definition
            _fragment_shader.source << "struct PointLight {";
            _fragment_shader.source << "    vec4 ambient;";
            _fragment_shader.source << "    vec4 diffuse;";
            _fragment_shader.source << "    vec4 specular;";

            _fragment_shader.source << "    vec3 position;";
            
            _fragment_shader.source << "    float kc;";
            _fragment_shader.source << "    float kl;";
            _fragment_shader.source << "    float kq;";
            _fragment_shader.source << "};";

            // spot light definition
            _fragment_shader.source << "struct SpotLight {";
            _fragment_shader.source << "    vec4 ambient;";
            _fragment_shader.source << "    vec4 diffuse;";
            _fragment_shader.source << "    vec4 specular;";

            _fragment_shader.source << "    vec3 position;";
            _fragment_shader.source << "    vec3 direction;";
            
            _fragment_shader.source << "    float range_inner;";
            _fragment_shader.source << "    float range_outer;";
            
            _fragment_shader.source << "    float kc;";
            _fragment_shader.source << "    float kl;";
            _fragment_shader.source << "    float kq;";
            _fragment_shader.source << "};";

            // input variables
            _fragment_shader.source << "in vec3 FragmentPosition;";
            
            _fragment_shader.source << "in vec3 NormalDirection;";
            _fragment_shader.source << "in vec2 TexturePosition;";

            // camera/viewer position
            _fragment_shader.source << "uniform vec3 camera_position;";

            // directional light
            _fragment_shader.source << "uniform DirectionalLight directional_light;";

            // point lights
            _fragment_shader.source << "uniform int point_light_count;";
            _fragment_shader.source << "uniform PointLight point_light[16];";

            // spot lights
            _fragment_shader.source << "uniform int spot_light_count;";
            _fragment_shader.source << "uniform SpotLight spot_light[16];";

            // material
            _fragment_shader.source << "uniform Material material;";

            // calcuate directional light color
            _fragment_shader.source << "vec4 calcuate_directional_light_color(DirectionalLight light, vec3 normalized_light_direction, vec3 normalized_normal_direction, vec3 normalized_camera_direction, vec4 diffuse_map_color, vec4 specular_map_color)"
                                        "{"
                                        "    float diffuse_factor = max(dot(normalized_normal_direction, normalized_light_direction), 0.0);"
                                        ""
                                        "    vec3 normalized_reflect_direction = reflect(-normalized_light_direction, normalized_normal_direction);"
                                        "    float specular_factor = pow(max(dot(normalized_camera_direction, normalized_reflect_direction), 0.0), material.shininess);"
                                        ""
                                        "    vec4 ambient_color = light.ambient * diffuse_map_color;"
                                        "    vec4 diffuse_color = light.diffuse * diffuse_factor * diffuse_map_color;"
                                        "    vec4 specular_color = light.specular * specular_factor * specular_map_color;"
                                        ""
                                        "    return (ambient_color + diffuse_color + specular_color);"
                                        "}";

            // calcuate point light color
            _fragment_shader.source << "vec4 calcuate_point_light_color(PointLight light, vec3 light_direction, vec3 normalized_normal_direction, vec3 normalized_camera_direction, vec4 diffuse_map_color, vec4 specular_map_color)"
                                        "{"
                                        "    vec3 normalized_light_direction = normalize(light_direction);"
                                        ""
                                        "    float diffuse_factor = max(dot(normalized_normal_direction, normalized_light_direction), 0.0);"
                                        ""
                                        "    vec3 normalized_reflect_direction = reflect(-normalized_light_direction, normalized_normal_direction);"
                                        "    float specular_factor = pow(max(dot(normalized_camera_direction, normalized_reflect_direction), 0.0), material.shininess);"
                                        ""
                                        "    float light_distance = length(light_direction);"
                                        "    float light_attenuation = 1.0 / (light.kc + light.kl * light_distance + light.kq * (light_distance * light_distance));"
                                        ""
                                        "    vec4 ambient_color = light.ambient * diffuse_map_color;"
                                        "    vec4 diffuse_color = light.diffuse * diffuse_factor * diffuse_map_color;"
                                        "    vec4 specular_color = light.specular * specular_factor * specular_map_color;"
                                        "    return (ambient_color + diffuse_color + specular_color) * light_attenuation;"
                                        "}";

            // calcuate spot light color
            _fragment_shader.source << "vec4 calcuate_spot_light_color(SpotLight light, vec3 light_direction, vec3 normalized_normal_direction, vec3 normalized_camera_direction, vec4 diffuse_map_color, vec4 specular_map_color)"
                                        "{"
                                        "    vec3 normalized_light_direction = normalize(light_direction);"
                                        ""
                                        "    float diffuse_factor = max(dot(normalized_normal_direction, normalized_light_direction), 0.0);"
                                        ""
                                        "    vec3 normalized_reflect_direction = reflect(-normalized_light_direction, normalized_normal_direction);"
                                        "    float specular_factor = pow(max(dot(normalized_camera_direction, normalized_reflect_direction), 0.0), material.shininess);"
                                        ""
                                        "    float light_distance = length(light_direction);"
                                        "    float light_attenuation = 1.0 / (light.kc + light.kl * light_distance + light.kq * (light_distance * light_distance));"
                                        ""
                                        "    float theta = dot(normalized_light_direction, -light.direction);"
                                        "    float epsilon = light.range_inner - light.range_outer;"
                                        "    float intensity = clamp((theta - light.range_outer) / epsilon, 0.0, 1.0);"
                                        ""
                                        "    vec4 ambient_color = light.ambient * diffuse_map_color;"
                                        "    vec4 diffuse_color = light.diffuse * diffuse_factor * diffuse_map_color;"
                                        "    vec4 specular_color = light.specular * specular_factor * specular_map_color;"
                                        "    return (ambient_color + diffuse_color + specular_color) * (light_attenuation * intensity);"
                                        "}";
            
            _fragment_shader.source << "void main()";
            _fragment_shader.source << "{";

            // get diffuse/specular map color
            _fragment_shader.source << "    vec4 diffuse_map_color = texture(material.diffuse, TexturePosition);";
            _fragment_shader.source << "    vec4 specular_map_color = texture(material.specular, TexturePosition);";

            // normalized normal direction
            _fragment_shader.source << "    vec3 normalized_normal_direction = normalize(NormalDirection);";

            // normalized camera/viewer direction
            _fragment_shader.source << "    vec3 normalized_camera_direction = normalize(camera_position - FragmentPosition);";

            // calculate directional light color
            _fragment_shader.source << "    vec4 result_color = calcuate_directional_light_color(directional_light, -directional_light.direction, normalized_normal_direction, normalized_camera_direction, diffuse_map_color, specular_map_color);";

            // calculate points light color
            _fragment_shader.source << "    for (int p = 0; p < point_light_count; ++p)";
            _fragment_shader.source << "    {";
            _fragment_shader.source << "        vec3 light_direction = point_light[p].position - FragmentPosition;";
            _fragment_shader.source << "        result_color += calcuate_point_light_color(point_light[p], light_direction, normalized_normal_direction, normalized_camera_direction, diffuse_map_color, specular_map_color);";
            _fragment_shader.source << "    }";

            // calculate spot light color
            _fragment_shader.source << "    for (int s = 0; s < spot_light_count; ++s)";
            _fragment_shader.source << "    {";
            _fragment_shader.source << "        vec3 light_direction = spot_light[s].position - FragmentPosition;";
            _fragment_shader.source << "        result_color += calcuate_spot_light_color(spot_light[s], light_direction, normalized_normal_direction, normalized_camera_direction, diffuse_map_color, specular_map_color);";
            _fragment_shader.source << "    }";

            _fragment_shader.source << "    FragColor = result_color;";
            _fragment_shader.source << "}";
        }

        PhongModel::~PhongModel()
        {
        }

        void PhongModel::UpdateCameraView(const entity::CameraPtr& camera)
        {
            _program.GetVariable("view").SetMat(camera->GetView());
            _program.GetVariable("projection").SetMat(camera->GetProjection());

            _program.GetVariable("camera_position").SetVec(camera->GetPosition());
        }

        void PhongModel::UpdateDirectionalLight(const light::DirectionalLightPtr& light)
        {
            _program.GetVariable("directional_light.direction").SetVec(light->GetDirection());

            _program.GetVariable("directional_light.ambient").SetVec(light->GetAmbient());
            _program.GetVariable("directional_light.diffuse").SetVec(light->GetDiffuse());
            _program.GetVariable("directional_light.specular").SetVec(light->GetSpecular());
        }

        void PhongModel::UpdatePointLights(const light::PointLights& lights)
        {
            GLint count = static_cast<GLint>(lights.size());

            _program.GetVariable("point_light_count").SetValue(count);

            for (GLint index = 0; index < Max_Point_Light_Size && index < count; ++index)
            {
                const light::PointLightPtr light = lights[index];
                
                const LightNameManager::PointLightPropertyName& property_name = lightNameManager.GetPointLightPropertyName(index);

                _program.GetVariable(property_name.position).SetVec(light->GetPosition());

                _program.GetVariable(property_name.ambient).SetVec(light->GetAmbient());
                _program.GetVariable(property_name.diffuse).SetVec(light->GetDiffuse());
                _program.GetVariable(property_name.specular).SetVec(light->GetSpecular());

                _program.GetVariable(property_name.kc).SetValue(light->GetAttenuationKc());
                _program.GetVariable(property_name.kl).SetValue(light->GetAttenuationKl());
                _program.GetVariable(property_name.kq).SetValue(light->GetAttenuationKq());
            }
        }

        void PhongModel::UpdateSpotLights(const light::SpotLights& lights)
        {
            GLint count = static_cast<GLint>(lights.size());

            _program.GetVariable("spot_light_count").SetValue(count);

            for (GLint index = 0; index < Max_Point_Light_Size && index < count; ++index)
            {
                const light::SpotLightPtr light = lights[index];
                
                const LightNameManager::SpotLightPropertyName& property_name = lightNameManager.GetSpotLightPropertyName(index);

                _program.GetVariable(property_name.position).SetVec(light->GetPosition());
                _program.GetVariable(property_name.direction).SetVec(light->GetDirection());

                _program.GetVariable(property_name.range_inner).SetValue(light->GetRangeInner());
                _program.GetVariable(property_name.range_outer).SetValue(light->GetRangeOuter());

                _program.GetVariable(property_name.ambient).SetVec(light->GetAmbient());
                _program.GetVariable(property_name.diffuse).SetVec(light->GetDiffuse());
                _program.GetVariable(property_name.specular).SetVec(light->GetSpecular());

                _program.GetVariable(property_name.kc).SetValue(light->GetAttenuationKc());
                _program.GetVariable(property_name.kl).SetValue(light->GetAttenuationKl());
                _program.GetVariable(property_name.kq).SetValue(light->GetAttenuationKq());
            }
        }

        void PhongModel::UpdateEntity(const entity::EntityPtr& entity)
        {
            const material::MaterialPtr& material = entity->GetMaterial();

            _program.GetVariable("material.shininess").SetValue(material->GetShininess());
            _program.GetVariable("material.diffuse").SetValue(material->GetDiffuse());
            _program.GetVariable("material.specular").SetValue(material->GetSpecular());

            _program.GetVariable("model").SetMat(entity->GetModel());
            _program.GetVariable("normal_model").SetMat(entity->GetNormalModel());
        }
    }
}
