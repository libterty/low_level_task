#include "async.h"

NAN_MODULE_INIT(async::Init)
{
    Nan::SetMethod(target, "doSyncStuff", DoSyncStuff);
    Nan::SetMethod(target, "doAsyncStuff", DoAsyncStuff);
}