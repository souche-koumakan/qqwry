/**
 *
 * QQWry - qqwry.dat parser and querier for Node.js.
 *
 * Copyright (c) 2017 XadillaX <i@2333.moe>
 *
 * MIT LIcense <https://github.com/souche-koumakan/qqwry/blob/master/LICENSE>
 */
#ifndef __QQWRY_H__
#define __QQWRY_H__
#include <nan.h>

extern "C" {
#include "libqqwry/qqwry.h"
}

namespace __node_qqwry__ {

class QQWry : public Nan::ObjectWrap {
public:
    static NAN_MODULE_INIT(Init);

public:
    qqwry_data_t* GetRaw();

private:
    explicit QQWry(const char* filename);
    ~QQWry();

    static NAN_METHOD(New);
    static NAN_METHOD(Init);
    static NAN_METHOD(Query);
    static NAN_METHOD(Destroy);

private:
    static v8::Persistent<v8::Function> constructor;
    qqwry_data_t raw;
    std::string filename;
};

}

#endif
