#include "libglsimplify_simple_text_renderer.h"

#include "entity/text/libglsimplify_text.h"

#include "entity/text/font/libglsimplify_free_type.h"
#include "entity/text/generator/libglsimplify_simple_generator.h"

namespace gl_simplify {

    namespace renderer::text {

        SimpleTextRenderer::SimpleTextRenderer()
            : BaseTextRenderer(CreateSimpleGeneratorOf())
        {
            // 顶点着色器
            _vertex_shader.source.Reset();
            _vertex_shader.source << "layout (location = 0) in vec3 position;";
            _vertex_shader.source << "layout (location = 1) in vec3 normal;";
            _vertex_shader.source << "layout (location = 2) in vec2 texcoord;";
            _vertex_shader.source << "";
            _vertex_shader.source << "out vec2 TexCoord;";
            _vertex_shader.source << "";
            _vertex_shader.source << "uniform mat4 model;";
            _vertex_shader.source << "uniform mat4 view;";
            _vertex_shader.source << "uniform mat4 projection;";
            _vertex_shader.source << "";
            _vertex_shader.source << "void main()";
            _vertex_shader.source << "{";
            _vertex_shader.source << "    gl_Position = projection * view * model * vec4(position, 1.0);";
            _vertex_shader.source << "    TexCoord = texcoord;";
            _vertex_shader.source << "}";

            // 片段着色器 - 简单的位图纹理渲染
            _fragment_shader.source.Reset();
            _fragment_shader.source << "in vec2 TexCoord;";
            _fragment_shader.source << "";
            _fragment_shader.source << "out vec4 FragColor;";
            _fragment_shader.source << "";
            _fragment_shader.source << "uniform sampler2D texture_unit;";
            _fragment_shader.source << "uniform vec4 text_color;";
            _fragment_shader.source << "";
            _fragment_shader.source << "void main()";
            _fragment_shader.source << "{";
            _fragment_shader.source << "    // 采样位图纹理的 alpha 通道";
            _fragment_shader.source << "    float alpha = texture(texture_unit, TexCoord).r;";
            _fragment_shader.source << "    ";
            _fragment_shader.source << "    // 直接使用文本颜色和纹理的 alpha";
            _fragment_shader.source << "    FragColor = vec4(text_color.rgb, text_color.a * alpha);";
            _fragment_shader.source << "}";
        }

        SimpleTextRenderer::~SimpleTextRenderer()
        {
        }

        void SimpleTextRenderer::updateShaderProgram() 
        {
            // 无需额外更新 uniform
        }

    }
}
