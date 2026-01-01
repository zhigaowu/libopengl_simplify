
#include "libglsimplify_character.h"

namespace gl_simplify {

    namespace entity::text {

        Character::Character(const font::CharacterGlyph& character_glyph, wchar_t character, bool render_both_faces)
            : BaseEntity(EntityType::Text)

            , _character(character)

            , _character_glyph(character_glyph)
        {
            // 创建一个简单的四边形（两个三角形）
            VertexDataBuffer vertices;
            IndexBuffer indices;

            // 顶点数据
            vertices.push_back({{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}});  // 左上
            vertices.push_back({{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}});  // 左下
            vertices.push_back({{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}});  // 右下
            vertices.push_back({{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}});  // 右上

            // 索引数据（两个三角形）
            indices = {0, 1, 2, 2, 3, 0};

            // 假如是双面渲染，则添加反面三角形
            if (render_both_faces)
            {
                indices.insert(indices.end(), {2, 1, 0, 0, 3, 2});
            }

            _index_count = static_cast<GLuint>(indices.size());

            createDefaultArrays();

            configureDefaultVertexAttributes(vertices, indices);
        }

        Character::~Character()
        {
        }

        void Character::Render()
        {
            _character_glyph.texture->ActiveUnit()->Bind();

            _vao->Bind();

            glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, 0);
            
            _vao->Unbind();
        }
    }
}
