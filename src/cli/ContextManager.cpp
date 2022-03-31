//
// Created by jeremy on 2022-03-25.
//

#include "cli/ContextManager.h"


bool ContextManager::SetContext(Context ctx)
{
    bool switched = false;
    switch (context) {
        case Welcome:
            switched = true;
            break;
        case Login:
        case Register:
            if (ctx == Main || ctx == Welcome)
                switched = true;
            break;
        case Main:
            if (ctx == Welcome)
                switched = true;
        default:
            break;
    }
    context = ctx;
    return switched;
}
