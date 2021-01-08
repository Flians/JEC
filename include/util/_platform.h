#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
   #else
      //define something for Windows (32-bit only)
   #endif
   #define WIN 1
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
        // #error "Unknown Apple platform"
    #endif
    #define DARWIN 1
#elif __linux__ || __linux
    #define LINUX 1
#elif __unix__ || __unix 
    #define UNIX 1
#elif defined(_POSIX_VERSION) || __posix
    #define POSIX 1
#else
    #define UNKNOWN 1
    // #error "Unknown compiler"
#endif