/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_base_text_renderer.h
 *
 *    Description:  Base Text Renderer
 *
 *        Version:  1.0
 *        Created:  2026-01-01 11:20:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDERER_TEXT_BASE_TEXT_RENDERER_H
#define GL_SIMPLIFY_RENDERER_TEXT_BASE_TEXT_RENDERER_H

#include "renderer/libglsimplify_base_renderer.h"

#include "entity/text/generator/libglsimplify_base_generator.h"

namespace gl_simplify {

    namespace renderer::text {

        class BaseTextRenderer : public BaseRenderer {
        private:
            entity::text::generator::BaseGeneratorPtr _character_generator;

        public:
            explicit BaseTextRenderer(const entity::text::generator::BaseGeneratorPtr& character_generator);
            ~BaseTextRenderer() override;

            const entity::text::generator::BaseGeneratorPtr& GetCharacterGenerator() const;

            void Render(const entity::BaseEntityPtr& entity) override;

        protected:
            virtual void updateShaderProgram() = 0;
        };

        using BaseTextRendererPtr = std::shared_ptr<BaseTextRenderer>;

    }
}

#endif // GL_SIMPLIFY_RENDERER_TEXT_BASE_TEXT_RENDERER_H
