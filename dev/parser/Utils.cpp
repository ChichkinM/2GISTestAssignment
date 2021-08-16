/*
 * \file Utils.cpp
 * \author : Chichkin M.A.
 * \date : 14.08.2021
 */

#include "Utils.h"

namespace doublegis {
namespace parser {
namespace utils {

bool isSeparator(char c) noexcept
{
    auto found = std::find(constants::separators.begin(),
                           constants::separators.end(), c);
    return found != constants::separators.end();
}

}
}
}
