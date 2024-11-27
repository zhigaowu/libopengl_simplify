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
            ~NonCopyable() = default;

            NonCopyable(const NonCopyable&) = delete;
            NonCopyable& operator=(const NonCopyable&) = delete;

            NonCopyable(NonCopyable&&) = delete;
            NonCopyable& operator=(NonCopyable&&) = delete;
        };

    }
}

#endif // GL_SIMPLIFY_CORE_TYPES_H
