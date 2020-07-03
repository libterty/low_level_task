#include "vector.h"

Nan::Persistent<v8::FunctionTemplate> Vector::constructor;

NAN_MODULE_INIT(Vector::Init)
{
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Vector::New);
    constructor.Reset(ctor);
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("Vector").ToLocalChecked());

    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Vector::HandleGetters, Vector::HandleSetters);
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Vector::HandleGetters, Vector::HandleSetters);
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), Vector::HandleGetters, Vector::HandleSetters);

    Nan::SetPrototypeMethod(ctor, "add", Add);

    target->Set(Nan::New("Vector").ToLocalChecked(), ctor->GetFunction());
}