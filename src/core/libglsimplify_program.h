/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_program.h
 *
 *    Description:  program logic
 *
 *        Version:  1.0
 *        Created:  2024-04-07 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_PROGRAM_H
#define GL_SIMPLIFY_CORE_PROGRAM_H

#include "libglsimplify_shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <functional>

namespace gl_simplify {

    namespace core {

        class Program {
            template<typename ValueType>
            struct UniformValueSetter
            {
                UniformValueSetter(GLint location, ValueType v0)
                {
                    glUniform1f(location, v0);
                }

                UniformValueSetter(GLint location, ValueType v0, GLfloat v1)
                {
                    glUniform2f(location, v0, v1);
                }

                UniformValueSetter(GLint location, ValueType v0, GLfloat v1, GLfloat v2)
                {
                    glUniform3f(location, v0, v1, v2);
                }

                UniformValueSetter(GLint location, ValueType v0, GLfloat v1, GLfloat v2, GLfloat v3)
                {
                    glUniform4f(location, v0, v1, v2, v3);
                }
            };

            template<>
            struct UniformValueSetter<GLdouble>
            {
                UniformValueSetter<GLdouble>(GLint location, GLdouble v0)
                {
                    glUniform1d(location, v0);
                }

                UniformValueSetter<GLdouble>(GLint location, GLdouble v0, GLdouble v1)
                {
                    glUniform2d(location, v0, v1);
                }

                UniformValueSetter<GLdouble>(GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
                {
                    glUniform3d(location, v0, v1, v2);
                }

                UniformValueSetter<GLdouble>(GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
                {
                    glUniform4d(location, v0, v1, v2, v3);
                }
            };

            template<>
            struct UniformValueSetter<GLint>
            {
                UniformValueSetter<GLint>(GLint location, GLint v0)
                {
                    glUniform1i(location, v0);
                }

                UniformValueSetter<GLint>(GLint location, GLint v0, GLint v1)
                {
                    glUniform2i(location, v0, v1);
                }

                UniformValueSetter<GLint>(GLint location, GLint v0, GLint v1, GLint v2)
                {
                    glUniform3i(location, v0, v1, v2);
                }

                UniformValueSetter<GLint>(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
                {
                    glUniform4i(location, v0, v1, v2, v3);
                }
            };

            template<>
            struct UniformValueSetter<GLuint>
            {
                UniformValueSetter<GLuint>(GLint location, GLuint v0)
                {
                    glUniform1ui(location, v0);
                }

                UniformValueSetter<GLuint>(GLint location, GLuint v0, GLuint v1)
                {
                    glUniform2ui(location, v0, v1);
                }

                UniformValueSetter<GLuint>(GLint location, GLuint v0, GLuint v1, GLuint v2)
                {
                    glUniform3ui(location, v0, v1, v2);
                }

                UniformValueSetter<GLuint>(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
                {
                    glUniform4ui(location, v0, v1, v2, v3);
                }
            };

            template<typename MatType>
            struct UniformMatSetter
            {
                UniformMatSetter(GLint location, GLboolean transpose, const MatType& mat)
                {
                    glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(mat));
                }
            };

            template<>
            struct UniformMatSetter<glm::mat3>
            {
                UniformMatSetter<glm::mat3>(GLint location, GLboolean transpose, const glm::mat3& mat)
                {
                    glUniformMatrix3fv(location, 1, transpose, glm::value_ptr(mat));
                }
            };

            template<>
            struct UniformMatSetter<glm::mat2>
            {
                UniformMatSetter<glm::mat2>(GLint location, GLboolean transpose, const glm::mat2& mat)
                {
                    glUniformMatrix2fv(location, 1, transpose, glm::value_ptr(mat));
                }
            };

            template<typename VecType>
            struct UniformVecSetter
            {
                UniformVecSetter(GLint location, const VecType& vec)
                {
                    glUniform4fv(location, 1, glm::value_ptr(vec));
                }
            };

            template<>
            struct UniformVecSetter<glm::vec3>
            {
                UniformVecSetter<glm::vec3>(GLint location, const glm::vec3& vec)
                {
                    glUniform3fv(location, 1, glm::value_ptr(vec));
                }
            };

            template<>
            struct UniformVecSetter<glm::vec2>
            {
                UniformVecSetter<glm::vec2>(GLint location, const glm::vec2& vec)
                {
                    glUniform2fv(location, 1, glm::value_ptr(vec));
                }
            };

            template<>
            struct UniformVecSetter<glm::vec1>
            {
                UniformVecSetter<glm::vec1>(GLint location, const glm::vec1& vec)
                {
                    glUniform1fv(location, 1, glm::value_ptr(vec));
                }
            };

            template<>
            struct UniformVecSetter<glm::ivec4>
            {
                UniformVecSetter<glm::ivec4>(GLint location, const glm::ivec4& vec)
                {
                    glUniform4iv(location, 1, glm::value_ptr(vec));
                }
            };

            template<>
            struct UniformVecSetter<glm::ivec3>
            {
                UniformVecSetter<glm::ivec3>(GLint location, const glm::ivec3& vec)
                {
                    glUniform3iv(location, 1, glm::value_ptr(vec));
                }
            };

            template<>
            struct UniformVecSetter<glm::ivec2>
            {
                UniformVecSetter<glm::ivec2>(GLint location, const glm::ivec2& vec)
                {
                    glUniform2iv(location, 1, glm::value_ptr(vec));
                }
            };

            template<>
            struct UniformVecSetter<glm::ivec1>
            {
                UniformVecSetter<glm::ivec1>(GLint location, const glm::ivec1& vec)
                {
                    glUniform1iv(location, 1, glm::value_ptr(vec));
                }
            };

        public:
            class Variable {
            public:
                GLint location;

            public:
                explicit Variable(GLint location = -1)
                    : location(location)
                {
                }

                ~Variable()
                {}

                Variable(Variable&& ref)
                    : location(ref.location)
                {
                }

                Variable& operator=(Variable&& ref)
                {
                    location = ref.location;
                    return *this;
                }

                Variable(const Variable& ref)
                    : location(ref.location)
                {
                }

                Variable& operator=(const Variable& ref)
                {
                    location = ref.location;
                    return *this;
                }

                template<typename ValueType>
                void SetValue(ValueType v0)
                {
                    UniformValueSetter(location, v0);
                }

                template<typename ValueType>
                void SetValue(ValueType v0, ValueType v1)
                {
                    UniformValueSetter(location, v0, v1);
                }

                template<typename ValueType>
                void SetValue(ValueType v0, ValueType v1, ValueType v2)
                {
                    UniformValueSetter(location, v0, v1, v2);
                }

                template<typename ValueType>
                void SetValue(ValueType v0, ValueType v1, ValueType v2, ValueType v3)
                {
                    UniformValueSetter(location, v0, v1, v2, v3);
                }

                template<typename MatType>
                void SetMat(const MatType& mat, GLboolean transpose = GL_FALSE)
                {
                    UniformMatSetter(location, transpose, mat);
                }

                template<typename VecType>
                void SetVec(const VecType& vec)
                {
                    UniformVecSetter(location, vec);
                }
            };

            using ProgramConfigurer = std::function<void(Program&)>;
            
        public:
            Program();
            ~Program();

            Program& Attach(const Shader& shader);

            bool Link(GLchar* error, GLsizei error_length);

            Program& Use();

            Program& Use(const ProgramConfigurer& program_configuer);

            Variable GetVariable(const std::string& vavriable_name);

        public:
            Program(Program&&) = delete;
            Program& operator=(Program&&) = delete;

            Program(const Program&) = delete;
            Program& operator=(const Program&) = delete;
        
        private:
            GLuint _program_id;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_PROGRAM_H
