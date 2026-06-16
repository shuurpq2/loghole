#ifndef LH_DEBUG_H
#define LH_DEBUG_H

#include <iostream>

#ifdef LH_DEBUG
    #define LH_DEBUG_PRINT(msg) std::cout << "[LH_DEBUG] " << msg << "\n";
#else
    #define LH_DEBUG_PRINT(msg) do {} while (0)
#endif

#endif