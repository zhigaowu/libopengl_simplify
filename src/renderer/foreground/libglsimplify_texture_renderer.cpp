
#include "libglsimplify_texture_renderer.h"

namespace gl_simplify {

    namespace renderer::foreground {

        TextureRenderer::TextureRenderer()
            : BasicRenderer()
        {
            _vertex_shader.source.Reset();
            // initialize vertext shader source
            _vertex_shader.source << "layout (location = 0) in vec3 entity_position;";
            _vertex_shader.source << "layout (location = 1) in vec3 entity_normal;";
            _vertex_shader.source << "layout (location = 2) in vec2 entity_texcoord;";

            _vertex_shader.source << "out vec2 TexCoord;";

            _vertex_shader.source << "uniform mat4 model;";
            _vertex_shader.source << "uniform mat4 view;";
            _vertex_shader.source << "uniform mat4 projection;";

            _vertex_shader.source << "void main()";
            _vertex_shader.source << "{" ;
            _vertex_shader.source << "    gl_Position = projection * view * model * vec4(entity_position, 1.0);";
            _vertex_shader.source << "    TexCoord = entity_texcoord;";
            _vertex_shader.source << "}";

            _fragment_shader.source.Reset();
            // initialize fragment shader source
            _fragment_shader.source << "in vec2 TexCoord;";
            _fragment_shader.source << "out vec4 FragColor;";

            // texture and color definition
            _fragment_shader.source << "uniform sampler2D texture_unit;";
            _fragment_shader.source << "uniform vec4 entity_color;";

            _fragment_shader.source << "void main()";
            _fragment_shader.source << "{";
            _fragment_shader.source << "    FragColor = texture(texture_unit, TexCoord) * entity_color;";
            _fragment_shader.source << "}";
        }

        TextureRenderer::~TextureRenderer()
        {
        }

        void TextureRenderer::Render(const entity::BaseEntityPtr &entity)
        {
            core::TexturePtr texture = entity->GetTexture();

            // 激活纹理单元并绑定纹理
            texture->ActiveUnit()->Bind();

            // 设置纹理单元索引到着色器
            _program.GetVariable("texture_unit").SetValue(texture->GetUnitIndex());

            BasicRenderer::Render(entity);
        }
    }
}
