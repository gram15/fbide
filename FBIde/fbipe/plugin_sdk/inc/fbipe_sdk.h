
#ifndef _FBIPE_SDK_H_
#define _FBIPE_SDK_H_

#include "class.plugin.data.h"
#include "class.plugin.h"

#define PLUGIN_EXPORT __declspec (dllexport)

#define DECLARE_PLUGIN() \
    extern "C" \
    { \
        PLUGIN_EXPORT classPlugin* GetPlugin(); \
    }
    
#define IMPLEMENT_PLUGIN(name) \
    classPlugin* GetPlugin() { return new name; }
    



#endif
