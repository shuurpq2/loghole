#pragma once

#include <string>

namespace lh {

class Utils {
public:
    static std::string get_timestamp();

    static std::string red(std::string str);
};

}