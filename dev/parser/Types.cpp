/*
 * \file Utils.cpp
 * \author : Chichkin M.A.
 * \date : 15.08.2021
 */

#include "Types.h"

namespace doublegis {
namespace parser {

bool WordAndCount::operator<(const WordAndCount &rhs) const noexcept
{
    if (count == rhs.count) {
        return word < rhs.word;
    }
    return count > rhs.count;
}

}
}
