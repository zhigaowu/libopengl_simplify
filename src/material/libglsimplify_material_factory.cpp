
#include "libglsimplify_material_factory.h"

namespace gl_simplify {

    namespace material {

        static MaterialFactory* instance = nullptr;

        MaterialFactory::MaterialFactory()
        {
        }

        MaterialFactory::~MaterialFactory()
        {
        }

        void MaterialFactory::Initialize()
        {
            if (!instance)
            {
                instance = new MaterialFactory();
            }
        }

        void MaterialFactory::Shutdown()
        {
            if (instance)
            {
                delete instance;
                instance = nullptr;
            }
        }

        MaterialFactory *MaterialFactory::Instance()
        {
            return instance;
        }

        SharedMaterial MaterialFactory::Create(GLuint texture_unit)
        {
            return std::make_shared<Material>(texture_unit);
        }
    }
}
