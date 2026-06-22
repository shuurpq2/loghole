#pragma once

#include <iostream>

#ifdef LH_DEBUG
    #define LH_DEBUG_PRINT(msg) std::cout << "[\033[1;36mLH_DEBUG\033[0m] " << msg << "\n";
#else
    #define LH_DEBUG_PRINT(msg) do {} while (0)
#endif