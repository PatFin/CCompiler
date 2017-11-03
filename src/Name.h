#pragma once

#include <string>

namespace Util
{
    class Name
    {
        public:
            std::string * name;
            int line;
            Name(std::string * n, int a);
    };
}
