
#include "libglsimplify_shader_source.h"

namespace gl_simplify {

    namespace core {

        ShaderSource::ShaderSource(const std::string& lines/* = ""*/)
            : _source_stream()
        {
            _source_stream << "#version " << GLVersion.major << GLVersion.minor << "0 core\n";
            _source_stream << lines << std::endl;
        }

        ShaderSource::~ShaderSource()
        {
        }

        ShaderSource &ShaderSource::operator<<(const std::string &lines)
        {
            _source_stream << lines << std::endl;

            return *this;
        }

        std::string ShaderSource::Code() const
        {
            return _source_stream.str();
        }
    }
}

