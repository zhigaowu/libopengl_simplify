
#include "libglsimplify_basic_renderer.h"

namespace gl_simplify {

    namespace renderer::foreground {

        BasicRenderer::BasicRenderer()
            : BaseRenderer()
        {
            // initialize vertext shader source
            _vertex_shader.source << "layout (location = 0) in vec3 entity_position;";

            _vertex_shader.source << "uniform mat4 model;";
            _vertex_shader.source << "uniform mat4 view;";
            _vertex_shader.source << "uniform mat4 projection;";

            _vertex_shader.source << "void main()";
            _vertex_shader.source << "{" ;
            _vertex_shader.source << "    gl_Position = projection * view * model * vec4(entity_position, 1.0);";
            _vertex_shader.source << "}";

            // initialize fragment shader source
            _fragment_shader.source << "out vec4 FragColor;";

            // color definition
            _fragment_shader.source << "uniform vec4 entity_color;";

            _fragment_shader.source << "void main()";
            _fragment_shader.source << "{";
            _fragment_shader.source << "    FragColor = entity_color;";
            _fragment_shader.source << "}";
        }

        BasicRenderer::~BasicRenderer()
        {
        }

        void BasicRenderer::Render(const entity::BaseEntityPtr &entity)
        {
            _program.GetVariable("entity_color").SetVec(entity->getColor());

            BaseRenderer::Render(entity);
        }
    }
}
