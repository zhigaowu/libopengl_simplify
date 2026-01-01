/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_base_entity.h
 *
 *    Description:  base class for entity in the scene
 *
 *        Version:  1.0
 *        Created:  2025-11-22 14:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_BASE_ENTITY_H
#define GL_SIMPLIFY_ENTITY_BASE_ENTITY_H

#include "core/libglsimplify_buffer_array.h"
#include "core/libglsimplify_vertex_array.h"

#include "core/libglsimplify_texture_buffer.h"

namespace gl_simplify {

    namespace entity {
        enum class EntityType {
            Basic = 0,
            Text = 1,
            Textured = 2,
            Lighted = 3,
            Count
        };

        // 顶点数据
        struct VertexData
        {
            glm::vec3 position; // 位置
            glm::vec3 normal;   // 法线
            glm::vec2 texcoord; // 纹理坐标
        };

        // 顶点数据缓冲区和索引缓冲区类型类型/别名
        using VertexDataBuffer = std::vector<VertexData>;
        using IndexBuffer = std::vector<GLuint>;

        class BaseEntity : private core::NonCopyable {
        private:
            EntityType _entity_type;

        protected:
            core::BufferArray* _vbo;
            core::BufferArray* _ebo;
            core::VertexArray* _vao;

        protected:
            GLuint _index_count;

        protected:
            glm::vec4 _color;
            core::TexturePtr _texture;

        protected:
            glm::mat4 _model;

        protected:
            void createDefaultArrays();
            void configureDefaultVertexAttributes(const VertexDataBuffer& vertices, const IndexBuffer& indices);
            void destroyArrays();
            
        public:
            explicit BaseEntity(EntityType type = EntityType::Basic);
            virtual ~BaseEntity();

            virtual void Render() = 0;

            EntityType GetType() const { return _entity_type; }

            void SetColor(const glm::vec4& color);
            const glm::vec4& GetColor() const { return _color; }

            void SetTexture(const core::TexturePtr& texture, bool reset_entity_type = true);
            const core::TexturePtr& GetTexture() const { return _texture; }

            void Translate(const glm::vec3& position);

            void TranslateTo(const glm::vec3& position);
            
            void Rotate(GLfloat degrees, const glm::vec3& axis);

            void Scale(const glm::vec3& size);

            const glm::mat4& GetModel() { return _model; }
        };

        using BaseEntityPtr = std::shared_ptr<BaseEntity>;

#define CreateDefaultEntity(Name) CreateDefault(Name)

    }
}

#endif // GL_SIMPLIFY_ENTITY_BASE_ENTITY_H
