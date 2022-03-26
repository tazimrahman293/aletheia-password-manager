//
// Created by jeremy on 2022-03-25.
//

#include "cli/ContextManager.h"


void ContextManager::SetContext(Context ctx)
{
    switch (context) {
        case Welcome:
            if (ctx == Login || ctx == Register)
                context = ctx;
            break;
        case Login:
        case Register:
            if (ctx == Main || ctx == Welcome)
                context = ctx;
            break;
        default:
            break;
    }
}
