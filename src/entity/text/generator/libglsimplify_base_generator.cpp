
#include "libglsimplify_base_generator.h"

namespace gl_simplify {

    namespace entity::text::generator {

        BaseGenerator::BaseGenerator()
            : core::NonCopyable()

            , _character_textures()
        {
        }

        BaseGenerator::~BaseGenerator()
        {
        }

        core::Texture2DPtr BaseGenerator::LookupLoadedTexture(wchar_t character) const
        {
            CharacterTextures::const_iterator it = _character_textures.find(character);
            
            if (it != _character_textures.end())
            {
                return it->second;
            }

            return nullptr;
        }

        core::Texture2DPtr BaseGenerator::GenerateTexture(wchar_t character, const unsigned char* bitmap, GLsizei width, GLsizei height)
        {
            // 创建新纹理
            core::Texture2DPtr texture = CreateTexture2D();

            core::Texture2D::TextureFormat format;
            format.gl_internalformat = GL_RED;
            format.channels = 1;
            format.data_type = GL_UNSIGNED_BYTE;
            format.level = 0;
            format.border = 0;
            format.flip_vertical = false;

            core::Texture2D::Dimension dimension{width, height};

            // 先构建纹理
            texture->Build(bitmap, format, dimension);
            
            // 为文字纹理设置特殊参数：
            // 1. 使用 CLAMP_TO_EDGE 避免边缘重复
            // 2. 使用 LINEAR 过滤以获得平滑的SDF采样
            // 3. 不使用 mipmap（MIN_FILTER 设为 LINEAR 而不是 LINEAR_MIPMAP_LINEAR）
            texture->Bind()
                ->SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
                ->SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
                ->SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                ->SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            _character_textures[character] = texture;

            return texture;
        }

    }
}
