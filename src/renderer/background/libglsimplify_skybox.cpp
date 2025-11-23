
#include "libglsimplify_skybox.h"

namespace gl_simplify {

    namespace renderer::background {

        SkyBox::SkyBox()
            : BaseEntity()

            , _sky_texture_buffer()
        {
        }

        SkyBox::~SkyBox()
        {
        }

        void SkyBox::Load(const std::string &path)
        {
            struct face_info {
                GLenum type;
                std::string file_name;
            };

            static const std::vector<face_info> faces_info{ 
                face_info{GL_TEXTURE_CUBE_MAP_POSITIVE_X, "/right.jpg"}, 
                face_info{GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "/left.jpg"}, 
                face_info{GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "/top.jpg"}, 
                face_info{GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "/bottom.jpg"}, 
                face_info{GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "/front.jpg"}, 
                face_info{GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "/back.jpg"}
            };

            core::TextureBuffer::Texture& texture = _sky_texture_buffer.GetTexture(0, GL_TEXTURE_CUBE_MAP);

            texture.Bind();

            for (size_t i = 0; i < faces_info.size(); ++i)
            {
                const face_info& face = faces_info[i];

                texture.UploadImage(face.type, path + face.file_name);
            }

            texture.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                    .SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
                    .SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
                    .SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
                    .SetParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            texture.Unbind();
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
            core::TextureBuffer::Texture& texture = _sky_texture_buffer.GetTexture();
            texture.Bind();

            _vao->Bind();

            glDrawArrays(GL_TRIANGLES, 0, 36);
            
            _vao->Unbind();

            texture.Unbind();
        }
    }
}

