/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_types.h
 *
 *    Description:  common used utilities
 *
 *        Version:  1.0
 *        Created:  2024-04-07 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_TYPES_H
#define GL_SIMPLIFY_CORE_TYPES_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <cmath>
#include <memory>
#include <vector>

#if __cplusplus < 202002L

namespace std {
    namespace numbers {
        const constexpr double pi = 3.141592653589793;
    }
}

#endif

namespace gl_simplify {

    namespace core {
        
        class NonCopyable {
        protected:
            NonCopyable() = default;
            virtual ~NonCopyable() = default;

            NonCopyable(const NonCopyable&) = delete;
            NonCopyable& operator=(const NonCopyable&) = delete;

            NonCopyable(NonCopyable&&) = delete;
            NonCopyable& operator=(NonCopyable&&) = delete;
        };

        using GLObjectID = GLuint;
        using GLObjectIDs = std::vector<GLObjectID>;
    }
}

#define DISABLE_DEFAULT_CONSTRUCT(ClassName) \
    ClassName() = delete;

#define CreateDefault(Name) std::make_shared<Name>()
#define CreateWithParameter(Name, ...) std::make_shared<Name>(__VA_ARGS__)

#endif // GL_SIMPLIFY_CORE_TYPES_H
