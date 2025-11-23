
#include "libglsimplify_skybox.h"

namespace gl_simplify {

    namespace renderer::background {

        SkyBox::SkyBox()
            : BaseEntity()

            , _sky_texture(CreateTextureCube())
        {
        }

        SkyBox::~SkyBox()
        {
        }

        void SkyBox::Load(const std::string &path)
        {
            _sky_texture->Bind();

            _sky_texture->Build(path);

            _sky_texture->SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                    ->SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
                    ->SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
                    ->SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
                    ->SetParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            _sky_texture->Unbind();
        }

        /*void SkyBox::Build()
        {
            static float skyboxVertices[] = {
                // positions          
                -1.0f,  1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                -1.0f,  1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f
            };

            createDefaultArrays();

            _vao->Bind();

            _vbo->Bind();
            _vbo->Upload(sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
            _vbo->SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            _vbo->Unbind();

            _vao->Unbind();
        }*/
        
        void SkyBox::Render()
        {
            _sky_texture->Bind();

            _vao->Bind();

            glDrawArrays(GL_TRIANGLES, 0, 36);
            
            _vao->Unbind();

            _sky_texture->Unbind();
        }
    }
}

