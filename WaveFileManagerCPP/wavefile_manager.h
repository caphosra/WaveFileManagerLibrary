#pragma once

#if NO_WRITE_FUNCS == 1
    #error NO_WRITE_FUNCS IS USED BY WAVEFILEMANAGER
#endif
#if NO_LOAD_FUNCS == 1
    #error NO_LOAD_FUNCS IS USED BY WAVEFILEMANAGER
#endif

#ifndef WITHOUT_WRITE_FUNCS
    #include"wavefile_writer.h"
#else
    #define NO_WRITE_FUNCS 1
#endif
#ifndef WITHOUT_LOAD_FUNCS
    #include"wavefile_loader.h"
#else
    #define NO_LOAD_FUNCS 1
#endif

#if NO_WRITE_FUNCS == 1 && NO_LOAD_FUNCS == 1
    #error WAVEFILEMANAGER HAS NO FUNCS
#endif

#ifndef WITHOUT_ASSIST_FUNCS
    #include"assistfuncs.h"
    #ifndef WITHOUT_INSTANCE_GENERATOR
        #include"instance_generator.h"
    #endif
#endif
