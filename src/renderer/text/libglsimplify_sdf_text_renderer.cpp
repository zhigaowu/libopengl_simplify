#include "libglsimplify_sdf_text_renderer.h"

#include "entity/text/libglsimplify_text.h"

#include "entity/text/font/libglsimplify_free_type.h"
#include "entity/text/generator/libglsimplify_sdf_generator.h"

namespace gl_simplify {

    namespace renderer::text {

        SDFTextRenderer::SDFTextRenderer()
            : BaseTextRenderer(CreateSDFGeneratorOf())
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

            // 片段着色器 - 实现 Valve SDF 渲染算法
            _fragment_shader.source.Reset();
            _fragment_shader.source << "in vec2 TexCoord;";
            _fragment_shader.source << "";
            _fragment_shader.source << "out vec4 FragColor;";
            _fragment_shader.source << "";
            _fragment_shader.source << "uniform sampler2D texture_unit;";
            _fragment_shader.source << "uniform vec4 text_color;";
            _fragment_shader.source << "uniform float smoothness;        // 边缘平滑度";
            _fragment_shader.source << "uniform float outline_width;     // 轮廓宽度 (0.0 - 0.5)";
            _fragment_shader.source << "uniform vec4 outline_color;      // 轮廓颜色";
            _fragment_shader.source << "";
            _fragment_shader.source << "void main()";
            _fragment_shader.source << "{";
            _fragment_shader.source << "    // 采样 SDF 纹理";
            _fragment_shader.source << "    float distance = texture(texture_unit, TexCoord).r;";
            _fragment_shader.source << "    ";
            _fragment_shader.source << "    // Valve 论文中的核心算法：";
            _fragment_shader.source << "    // 使用屏幕空间导数自适应计算抗锯齿宽度";
            _fragment_shader.source << "    float edge_distance = 0.5;  // 边缘阈值";
            _fragment_shader.source << "    ";
            _fragment_shader.source << "    // 使用 fwidth 获得屏幕空间的变化率，自动适应缩放";
            _fragment_shader.source << "    float smoothing = fwidth(distance) * 0.5;";
            _fragment_shader.source << "    smoothing = max(smoothing, smoothness);  // 使用用户设置和自动计算的较大值";
            _fragment_shader.source << "    ";
            _fragment_shader.source << "    float alpha = smoothstep(edge_distance - smoothing, edge_distance + smoothing, distance);";
            _fragment_shader.source << "    ";
            _fragment_shader.source << "    // 计算轮廓";
            _fragment_shader.source << "    if (outline_width > 0.0)";
            _fragment_shader.source << "    {";
            _fragment_shader.source << "        float outline_edge = edge_distance - outline_width;";
            _fragment_shader.source << "        float outline_alpha = smoothstep(outline_edge - smoothing, outline_edge + smoothing, distance);";
            _fragment_shader.source << "        ";
            _fragment_shader.source << "        // 混合轮廓和文字颜色";
            _fragment_shader.source << "        vec4 result_color = mix(outline_color, text_color, outline_alpha);";
            _fragment_shader.source << "        FragColor = vec4(result_color.rgb, result_color.a * alpha);";
            _fragment_shader.source << "    }";
            _fragment_shader.source << "    else";
            _fragment_shader.source << "    {";
            _fragment_shader.source << "        FragColor = vec4(text_color.rgb, text_color.a * alpha);";
            _fragment_shader.source << "    }";
            _fragment_shader.source << "}";
        }

        SDFTextRenderer::~SDFTextRenderer()
        {
        }

        void SDFTextRenderer::updateShaderProgram() 
        {
            entity::text::generator::SDFGeneratorPtr sdf_gen = std::dynamic_pointer_cast<entity::text::generator::SDFGenerator>(
                GetCharacterGenerator()
            );

            // 设置 uniform
            _program.GetVariable("smoothness").SetValue(sdf_gen->GetSmoothness());
            _program.GetVariable("outline_width").SetValue(sdf_gen->GetOutlineWidth());
            _program.GetVariable("outline_color").SetVec(sdf_gen->GetOutlineColor());
        }

    }
}
