#include <nan.h>

class asyncBinding
{
public:
    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(DoSyncStuff);
    static NAN_METHOD(DOAsyncStuff);
}