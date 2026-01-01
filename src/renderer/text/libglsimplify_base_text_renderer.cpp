#include "libglsimplify_base_text_renderer.h"

#include "entity/text/libglsimplify_text.h"

#include "entity/text/font/libglsimplify_free_type.h"

namespace gl_simplify {

    namespace renderer::text {

        BaseTextRenderer::BaseTextRenderer(const entity::text::generator::BaseGeneratorPtr& character_generator)
            : BaseRenderer()

            , _character_generator(character_generator)
        {
        }

        BaseTextRenderer::~BaseTextRenderer()
        {
        }

        const entity::text::generator::BaseGeneratorPtr &BaseTextRenderer::GetCharacterGenerator() const
        {
            return _character_generator;
        }

        void BaseTextRenderer::Render(const entity::BaseEntityPtr& entity) 
        {
            auto text = std::dynamic_pointer_cast<entity::text::Text>(entity);
            if (!text) 
            {
                return;  // 不是 Text 实体，直接返回
            }
            
            // 设置渲染器参数
            updateShaderProgram();

            // 绑定纹理单元
            _program.GetVariable("text_color").SetVec(text->GetColor());
            _program.GetVariable("texture_unit").SetValue(0);
            
            // 渲染所有字符
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            // 获取 Text 的整体变换矩阵
            glm::mat4 text_transform = text->GetModel();
            
            for (const auto& character : text->GetCharacters()) 
            {
                // 组合 Text 的变换和 Character 的变换
                glm::mat4 final_model = text_transform * character->GetModel();
                _program.GetVariable("model").SetMat(final_model);
                character->Render();
            }
            
            glDisable(GL_BLEND);
        }

    }
}
