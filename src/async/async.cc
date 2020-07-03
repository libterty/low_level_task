#include "async.h"

NAN_MODULE_INIT(async::Init)
{
    Nan::SetMethod(target, "doSyncStuff", DoSyncStuff);
    Nan::SetMethod(target, "doAsyncStuff", DoAsyncStuff);
}

void delay(int iterations)
{
    for (volatile int i = 0; i < iterations; i++);
}

NAN_METHOD(AsyncBinding::DoSyncStuff)
{
    if (!info[0]->IsString())
    {
        return Nan::ThrowError(Nan::New("expected arg 0: string workerId").ToLocalChecked());
    }
    if(!info[1]->IsInt32()) 
    {
        return Nan::ThrowError(Nan::New("expected arg 1: int iterations").ToLocalChecked());
    }

    std::string workerId = std::string(*Nan::Utf8string(info[0]->ToString()));
    int iterations = info[1]->Int32Value();

    delay(iterations);

    info.GetReturnValue().Set(Nan::New(workerId).ToLocalChecked());
}

class AsyncWorker : public Nan::AsyncWorker
{
public:
    std::string workerId;
    int iterations;
    bool throwsError;

    AsyncWorker(std::string workerId, int iterations, bool throwsError, Nan::Callback *callback): Nan::AsyncWorker(callback)
    {
        this->workerId = workerId;
        this->iterations = iterations;
        this->throwsError = throwsError:
    }

    void Execute()
    {
        if (throwsError)
        {
            this->SetErrorMessage("An Error Occuerd");
            return;
        }

        delay(iterations);
    }

    void HandleOKCallback()
    {
        Nan::HandleScope scope;
        v8::Local<v8::Value> argv[] = {
            Nan::Null(),
            Nan::New(workerId).ToLocalChecked()
        };
        Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), 2, argv);
    }

    void HandleErrorCallback()
    {
        Nan::HandleScope scope;
        v8::Local<v8::Value> argv[] = {
            Nan::New(this->ErrorMessage().ToLocalChecked()),
            Nan::Null()
        };
        Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), 2, argv);
    }
}

NAN_METHOD(AsyncBinding::DoAsyncStuff)
{
    if(!info[0]->IsString()) 
    {
        return Nan::ThrowError(Nan::New("expected arg 0: string workerId").ToLocalChecked());
    }
    if(!info[1]->IsInt32()) 
    {
        return Nan::ThrowError(Nan::New("expected arg 1: int iterations").ToLocalChecked());
    }
    if(!info[2]->IsBoolean()) 
    {
        return Nan::ThrowError(Nan::New("expected arg 2: bool throwsError").ToLocalChecked());
    }
    if(!info[3]->IsFunction()) 
    {
        return Nan::ThrowError(Nan::New("expected arg 3: function callback").ToLocalChecked());
    }

    Nan::AsyncQueueWorker(new AsyncWorker(
        std::string(*Nan::Utf8String(info[0]->ToString()));
        info[1]->Int32Value();
        info[2]->BooleanValue();
        new Nan::Callback(info[3].As<v8::Function>());
    ));
}