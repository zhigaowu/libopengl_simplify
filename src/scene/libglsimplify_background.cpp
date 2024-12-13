
#include "libglsimplify_background.h"

namespace gl_simplify {

    namespace scene {

        Background::Background()
            : _color(0.0, 0.0, 0.0, 1.0)
            , _sky_box()
        {
            // initialize vertext shader source
            _vertex_shader.source << "layout (location = 0) in vec3 fragment_local_position;";

            _vertex_shader.source << "out vec3 TexturePosition;";

            _vertex_shader.source << "uniform mat4 view;";
            _vertex_shader.source << "uniform mat4 projection;";

            _vertex_shader.source << "void main()";
            _vertex_shader.source << "{" ;
            _vertex_shader.source << "    TexturePosition = fragment_local_position;";

            _vertex_shader.source << "    vec4 fragment_position = projection * view * vec4(fragment_local_position, 1.0);";
            _vertex_shader.source << "    gl_Position = fragment_position.xyww;";
            _vertex_shader.source << "}";

            // initialize fragment shader source
            _fragment_shader.source << "out vec4 FragColor;";

            _fragment_shader.source << "in vec3 TexturePosition;";

            // sky box texture
            _fragment_shader.source << "uniform samplerCube skybox;";
            
            _fragment_shader.source << "void main()";
            _fragment_shader.source << "{";

            _fragment_shader.source << "    FragColor = texture(skybox, TexturePosition);";
            _fragment_shader.source << "}";
        }

        Background::~Background()
        {
        }

        void Background::SetColor(const glm::vec4 &color)
        {
            _color = color;
        }

        void Background::Clear()
        {
            glClearColor(_color.r, _color.g, _color.b, _color.a);
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        bool Background::LoadSkyBox(const std::string &path, GLchar* error, GLsizei error_length)
        {
            if (!_sky_box)
            {
                _sky_box = CreateSkyBox();

                _sky_box->Create();
            }

            _sky_box->Load(path);

            if (Build(error, error_length))
            {
                glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
                
                _program.GetVariable("skybox").SetValue(0);

                return true;
            }

            return false;
        }

        void Background::Render()
        {
            if (_sky_box)
            {
                glDepthFunc(GL_LEQUAL);

                _sky_box->Render();

                glDepthFunc(GL_LESS);
            }
        }

        void Background::UpdateCameraView(const entity::CameraPtr &camera)
        {
            if (_sky_box)
            {
                _program.GetVariable("view").SetMat(glm::mat4(glm::mat3(camera->GetView()))); // remove transformation
                _program.GetVariable("projection").SetMat(camera->GetProjection());
            }
        }

        void Background::UpdateDirectionalLight(const light::DirectionalLightPtr &light)
        {
        }

        void Background::UpdatePointLights(const light::PointLights &lights)
        {
        }

        void Background::UpdateSpotLights(const light::SpotLights &lights)
        {
        }

        void Background::UpdateEntity(const entity::EntityPtr &entity)
        {
        }
    }
}

