#include <nan.h>
#include "qqwry.h"

namespace __node_qqwry__ {

NAN_MODULE_INIT(Init)
{
    QQWry::Init(target);
}

}

NODE_MODULE(qqwry, __node_qqwry__::Init)
