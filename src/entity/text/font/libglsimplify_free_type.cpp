
#include "libglsimplify_free_type.h"

#include "logger/libglsimplify_logger.h"

namespace gl_simplify {

    namespace entity::text::font {

#define Get_TrueType_Error_String(error_code, error_string) if (error_string) (*(error_string)) = FT_Error_String(error_code)

        Face::Face(const FaceParameter& parameter, FT_Face face)
            : core::NonCopyable()

            , _parameter(parameter)
            
            , _face(face)
        {
        }

        Face::~Face()
        {
            if (_face)
            {
                FT_Done_Face(_face);
                _face = nullptr;
            }
        }

        const FaceParameter &Face::GetParameter() const
        {
            return _parameter;
        }

        FT_Face Face::GetFTFace() const
        {
            return _face;
        }

        CharacterGlyph Face::LoadCharacter(FT_ULong char_code, const generator::BaseGeneratorPtr& generator, std::string* error_message)
        {
            // 加载字符
            CharacterGlyph character_glyph;
            if (_face)
            {
                FT_Error error_code = FT_Load_Char(_face, char_code, FT_LOAD_RENDER);

                if (!error_code)
                {
                    FT_GlyphSlot glyph = _face->glyph;

                    character_glyph.size = glm::ivec2(glyph->bitmap.width, glyph->bitmap.rows);
                    character_glyph.bearing = glm::ivec2(glyph->bitmap_left, glyph->bitmap_top);
                    character_glyph.advance = static_cast<GLuint>(glyph->advance.x >> 6); // 1/64 像素单位转换为像素单位

                    // 查找是否已经加载过该字符的纹理
                    if (!(character_glyph.texture = generator->LookupLoadedTexture(char_code)))
                    {
                        // 生成纹理
                        character_glyph.texture = generator->GenerateTexture(
                            char_code,
                            glyph->bitmap.buffer,
                            static_cast<GLsizei>(glyph->bitmap.width),
                            static_cast<GLsizei>(glyph->bitmap.rows)
                        );
                    }
                }
                else
                {
                    Get_TrueType_Error_String(error_code, error_message);
                }
            }

            return character_glyph;
        }

        FreeType::FreeType()
            : _ft_library(nullptr)

            , _loaded_faces()
        {
            FT_Init_FreeType(&_ft_library);
        }

        FreeType::~FreeType()
        {
            // 清理已加载的字体
            _loaded_faces.clear();

            // 释放 FreeType 库
            if (_ft_library)
            {
                FT_Done_FreeType(_ft_library);
                _ft_library = nullptr;
            }
        }

        FacePtr FreeType::LoadFace(const FaceParameter &parameter, std::string* error_message)
        {
            if (_ft_library)
            {
                // 先检查是否已经加载过
                FaceFamilyMap::iterator familyIt = _loaded_faces.find(parameter.font_path);
                if (familyIt != _loaded_faces.end())
                {
                    FaceHeightMap::iterator heightIt = familyIt->second.find(parameter.font_height);
                    if (heightIt != familyIt->second.end())
                    {
                        return heightIt->second;
                    }
                }

                FT_Face face = nullptr;

                FT_Error error_code = FT_New_Face(
                    _ft_library,
                    parameter.font_path.c_str(),
                    parameter.face_index,
                    &face
                );

                if (!error_code)
                {
                    // 设置像素尺寸
                    if (!(error_code = FT_Set_Pixel_Sizes(face, 0, parameter.font_height)))
                    {
                        // 构造 Face 对象
                        FacePtr face_ptr = std::make_shared<Face>(parameter, face);

                        if (familyIt != _loaded_faces.end())
                        {
                            familyIt->second.insert(std::make_pair(parameter.font_height, face_ptr));
                        }
                        else
                        {
                            FaceHeightMap height_map;
                            height_map.insert(std::make_pair(parameter.font_height, face_ptr));

                            _loaded_faces.insert(std::make_pair(parameter.font_path, height_map));
                        }

                        return face_ptr;
                    }
                    else
                    {
                        glError("Failed to set pixel size for font face(" << parameter.font_path << "): " << error_message);
                    }
                }
                else
                {
                    Get_TrueType_Error_String(error_code, error_message);
                }
            }

            return nullptr;
        }

        FreeType &FreeType::Instance()
        {
            static FreeType instance;

            return instance;
        }
    }
}

