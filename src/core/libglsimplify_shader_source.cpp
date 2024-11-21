
#include "libglsimplify_shader_source.h"

namespace gl_simplify {

    namespace core {

        ShaderSource::ShaderSource(const std::string& source/* = ""*/)
            : _source_stream()
        {
            _source_stream << "#version " << GLVersion.major << GLVersion.minor << "0 core\n";
            _source_stream << source << std::endl;
        }

        ShaderSource::~ShaderSource()
        {
        }

        ShaderSource& ShaderSource::operator<<(const char* source)
        {
            _source_stream << source << std::endl;

            return *this;
        }

        ShaderSource &ShaderSource::operator<<(const std::string & source)
        {
            _source_stream << source << std::endl;

            return *this;
        }

        std::string ShaderSource::Source() const
        {
            return _source_stream.str();
        }
    }
}

