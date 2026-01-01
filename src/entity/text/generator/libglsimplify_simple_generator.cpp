
#include "libglsimplify_simple_generator.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace gl_simplify {

    namespace entity::text::generator {

        SimpleGenerator::SimpleGenerator(const SimpleControl& simple_control)
            : BaseGenerator()

            , _simple_control(simple_control)
        {
        }

        SimpleGenerator::~SimpleGenerator()
        {
        }

        core::Texture2DPtr SimpleGenerator::GenerateTexture(wchar_t character, const unsigned char* bitmap, GLsizei width, GLsizei height)
        {
            // 创建并返回纹理对象
            return BaseGenerator::GenerateTexture(character, bitmap, width, height);
        }

    }
}
