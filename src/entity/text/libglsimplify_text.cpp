#include "libglsimplify_text.h"

#include "entity/text/generator/libglsimplify_sdf_generator.h"

#include "logger/libglsimplify_logger.h"

namespace gl_simplify {

    namespace entity::text {

        Text::Text(const std::wstring& text, GLuint pixel_size, const TextParameter& parameter)
            : BaseEntity(EntityType::Text)

            , _text(text)
            , _pixel_size(pixel_size)

            , _parameter(parameter)

            , _face(nullptr)

            , _characters()
        {
        }

        Text::~Text()
        {
        }

        GLuint Text::GetPixelSize() const
        {
            return _pixel_size;
        }

        const Characters &Text::GetCharacters() const
        {
            return _characters;
        }

        bool Text::Generate(const generator::BaseGeneratorPtr& generator, std::string* error_message)
        {
            if (!_face || _face->GetParameter().font_path != _parameter.font_path)
            {
                // 加载字体面
                font::FaceParameter face_param(_parameter.font_path, _parameter.font_height);

                _face = font::FreeType::Instance().LoadFace(face_param, error_message);

                _characters.clear();
            }

            // 加载字符
            if (_face)
            {
                GLfloat x = 0.0f;  // 当前渲染位置
                GLfloat scale = static_cast<GLfloat>(_pixel_size) / static_cast<GLfloat>(_parameter.font_height);  // 缩放比例
                GLfloat world_scale = 0.01f;  // 像素到世界坐标的转换比例
                
                glInfo("Loading text: \"" << std::wstring(_text.begin(), _text.end()).c_str() << "\" with " << _text.length() << " characters");
                glInfo("Font scale: " << scale << " (pixel_size: " << _pixel_size << "), world_scale: " << world_scale);
                
                // 为每个字符创建实体
                for (wchar_t ch : _text)
                {
                    font::CharacterGlyph glyph = _face->LoadCharacter(ch, generator, error_message);
                    
                    if (glyph.texture) 
                    {
                        CharacterPtr character = CreateCharacterOf(glyph, ch, _parameter.render_both_faces);
                        character->SetColor(_color);
                        
                        // 计算位置（应用世界坐标缩放）
                        GLfloat xpos = x + glyph.bearing.x * scale;
                        GLfloat ypos = -(glyph.size.y - glyph.bearing.y) * scale;
                        
                        glInfo("Character '" << (char)ch << "': pos(" << xpos * world_scale << ", " << ypos * world_scale << "), size(" 
                               << glyph.size.x * scale * world_scale << ", " << glyph.size.y * scale * world_scale << ")");
                        
                        // 设置变换（应用世界坐标缩放）
                        character->TranslateTo(glm::vec3(xpos * world_scale, ypos * world_scale, 0.0f));
                        character->Scale(glm::vec3(glyph.size.x * scale * world_scale, 
                                                  glyph.size.y * scale * world_scale, 
                                                  1.0f));
                        
                        _characters.push_back(character);
                        
                        // 移动到下一个字符位置
                        x += glyph.advance * scale;
                    }
                    else 
                    {
                        glError("Failed to load character('" << static_cast<int>(ch) << "'): " << error_message);
                        break;
                    }
                }
                
                glInfo("Total text width: " << x * world_scale);
            }

            return !_characters.empty();
        }

        void Text::Render()
        {
            // 渲染由渲染器批处理完成，这里不需要实现
        }
    }
}

