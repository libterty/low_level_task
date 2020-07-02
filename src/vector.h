#include <nan.h>

class Vector : public Nan::ObjectWrap
{
public:
    // properteries
    double x;
    double y;
    double z;

    static NAN_MODULE_INIT(int);
    static NAN_METHOD(New);
    static NAN_METHOD(Add);

    // Get and Setter
    static NAN_GETTER(HandleGetters);
    static NAN_SETTER(HandleSetters);

    static Nan::Persistent<v8::FunctionTemplate> constructor;
}