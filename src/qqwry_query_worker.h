/**
 *
 * QQWry - qqwry.dat parser and querier for Node.js.
 *
 * Copyright (c) 2017 XadillaX <i@2333.moe>
 *
 * MIT LIcense <https://github.com/souche-koumakan/qqwry/blob/master/LICENSE>
 */
#ifndef __QQWRY_QUERY_WORKER_H__
#define __QQWRY_QUERY_WORKER_H__
#include <string>
#include <nan.h>
#include "qqwry.h"
using namespace std;

namespace __node_qqwry__ {

using v8::Local;
using v8::Object;
using v8::Value;

char __empty_str = '\0';

class QQWryQueryWorker : public Nan::AsyncWorker {
public:
    QQWryQueryWorker(Nan::Callback* callback, uint32_t ip, QQWry* qqwry) :
        AsyncWorker(callback),
        ip(ip),
        qqwry(qqwry)
    {
        memset(&ret, 0, sizeof(qqwry_result_t));
    }

    ~QQWryQueryWorker()
    {
    }

    void Execute()
    {
        qqwry_data_t* raw = qqwry->GetRaw();
        qqwry_query(*raw, ip, &ret);
        if(!ret.country && !ret.area)
            this->SetErrorMessage("Cannot locate this IP.");
    }

    void HandleOKCallback()
    {
        Nan::HandleScope scope;

        char* country_str = ret.country ? ret.country : &__empty_str;
        char* area_str = ret.area ? ret.area : &__empty_str;

        Local<Object> country = Nan::CopyBuffer(country_str, strlen(country_str)).ToLocalChecked();
        Local<Object> area = Nan::CopyBuffer(area_str, strlen(area_str)).ToLocalChecked();
        Local<Value> ret[3] = { Nan::Undefined(), country, area };
        callback->Call(3, ret);
    }

private:
    uint32_t ip;
    QQWry* qqwry;
    qqwry_result_t ret;
};

}

#endif
