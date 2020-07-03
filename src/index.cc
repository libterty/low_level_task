#include <nan.h>
#include "vector.h"

NAN_MODULE_INIT(InitModule)
{
    Vector::Init(target);
}

NODE_MODULE(module, InitModule);