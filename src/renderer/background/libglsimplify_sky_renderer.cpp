
#include "libglsimplify_sky_renderer.h"

namespace gl_simplify {

    namespace renderer::background {

        SkyRenderer::SkyRenderer()
            : BasicRenderer()

            , _sky_box()
        {
            // initialize vertext shader source
            _vertex_shader.source.Reset();

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
            _fragment_shader.source.Reset();
            
            _fragment_shader.source << "out vec4 FragColor;";

            _fragment_shader.source << "in vec3 TexturePosition;";

            // sky box texture
            _fragment_shader.source << "uniform samplerCube skybox;";
            
            _fragment_shader.source << "void main()";
            _fragment_shader.source << "{";

            _fragment_shader.source << "    FragColor = texture(skybox, TexturePosition);";
            _fragment_shader.source << "}";
        }

        SkyRenderer::~SkyRenderer()
        {
        }

        bool SkyRenderer::LoadSkyBox(const std::string &path, GLchar* error, GLsizei error_length)
        {
            if (!_sky_box)
            {
                _sky_box = CreateSkyBox();

                //_sky_box->Build();
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

        void SkyRenderer::Render(const entity::BaseEntityPtr& entity)
        {
            if (_sky_box)
            {
                glDepthFunc(GL_LEQUAL);

                _sky_box->Render();

                glDepthFunc(GL_LESS);
            }
        }
    }
}

