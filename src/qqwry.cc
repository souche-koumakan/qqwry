#include "qqwry.h"
#include "qqwry_init_worker.h"
#include "qqwry_query_worker.h"

namespace __node_qqwry__ {

using v8::Function;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::String;
using v8::Persistent;
using v8::Uint32;

Persistent<Function> QQWry::constructor;

NAN_MODULE_INIT(QQWry::Init)
{
    Isolate* isolate = target->GetIsolate();

    Local<FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("QQWryInner").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "init", Init);
    Nan::SetPrototypeMethod(tpl, "query", Query);
    Nan::SetPrototypeMethod(tpl, "destroy", Destroy);

    constructor.Reset(isolate, Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(
            target,
            Nan::New("QQWryInner").ToLocalChecked(),
            Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(QQWry::New)
{
    Nan::Utf8String filename(info[0]->ToString());

    QQWry* obj = new QQWry(*filename);

    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(QQWry::Init)
{
    QQWry* obj = ObjectWrap::Unwrap<QQWry>(info.Holder());
    Nan::Callback* cb = new Nan::Callback(info[0].As<Function>());
    AsyncQueueWorker(new QQWryInitWorker(cb, obj->filename, obj));
}

NAN_METHOD(QQWry::Query)
{
    QQWry* obj = ObjectWrap::Unwrap<QQWry>(info.Holder());
    uint32_t ip = Nan::To<uint32_t>(info[0]).FromJust();
    Nan::Callback* cb = new Nan::Callback(info[1].As<Function>());
    AsyncQueueWorker(new QQWryQueryWorker(cb, ip, obj));
}

NAN_METHOD(QQWry::Destroy)
{
    QQWry* obj = ObjectWrap::Unwrap<QQWry>(info.Holder());
    qqwry_clean(*obj->GetRaw());
}

QQWry::QQWry(const char* filename) :
    filename(filename)
{
}

QQWry::~QQWry()
{
}

qqwry_data_t* QQWry::GetRaw()
{
    return &raw;
}

}
