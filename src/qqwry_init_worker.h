/**
 *
 * QQWry - qqwry.dat parser and querier for Node.js.
 *
 * Copyright (c) 2017 XadillaX <i@2333.moe>
 *
 * MIT LIcense <https://github.com/souche-koumakan/qqwry/blob/master/LICENSE>
 */
#ifndef __QQWRY_INIT_WORKER_H__
#define __QQWRY_INIT_WORKER_H__
#include <string>
#include <nan.h>
#include "qqwry.h"
using namespace std;

namespace __node_qqwry__ {

class QQWryInitWorker : public Nan::AsyncWorker {
public:
    QQWryInitWorker(Nan::Callback* callback, string filename, QQWry* qqwry) :
        AsyncWorker(callback),
        filename(filename),
        qqwry(qqwry)
    {
    }

    ~QQWryInitWorker()
    {
    }

    void Execute()
    {
        qqwry_data_t* raw = qqwry->GetRaw();

        char name[filename.size() + 1];
        memcpy(name, filename.c_str(), filename.size() + 1);
        int ret = qqwry_init(name, raw);

        char err_str[512];
        if(ret == 1)
        {
            snprintf(err_str, 512, "Cannot open qqwrt file. %s", filename.c_str());
            this->SetErrorMessage(err_str);
        }
        else
        if(ret == 2)
        {
            this->SetErrorMessage("Cannot alloc more buffer for qqwrt raw data.");
        }
        else
        if(ret == 3)
        {
            snprintf(err_str, 512, "Cannot read data from qqwrt file. %s", filename.c_str());
            this->SetErrorMessage(err_str);
        }
        else
        if(ret)
        {
            snprintf(err_str, 512, "Unknown init error %d.", ret);
            this->SetErrorMessage(err_str);
        }
    }

private:
    string filename;
    QQWry* qqwry;
};

}

#endif
