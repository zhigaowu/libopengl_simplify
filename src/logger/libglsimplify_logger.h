/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_logger.h
 *
 *    Description:  logger and common types
 *
 *        Version:  1.0
 *        Created:  2024-04-07 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_LOGGER_H
#define GL_SIMPLIFY_LOGGER_H

#include <iostream>

namespace gl_simplify {

    namespace logger {
        
        enum class Level {
            Debug,
            Info,
            Warning,
            Error
        };
        
    }
}

#define glDebug(...) std::cout << __VA_ARGS__ << " " << __FILE__ << ":" << __LINE__ << std::endl;
#define glInfo(...) std::cout << __VA_ARGS__ << " " << __FILE__ << ":" << __LINE__ << std::endl;
#define glWarning(...) std::cout << __VA_ARGS__ << " " << __FILE__ << ":" << __LINE__ << std::endl;
#define glError(...) std::cerr << __VA_ARGS__ << " " << __FILE__ << ":" << __LINE__ << std::endl;

#endif // GL_SIMPLIFY_LOGGER_H
