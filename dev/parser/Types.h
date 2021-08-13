/*
 * \file Types.h
 * \author : Chichkin M.A.
 * \date : 12.08.2021
 */

#pragma once

#include <array>
#include <QByteArray>

namespace doublegis {
namespace parser {

namespace constants {
const std::array<char, 2> separators{' ', '\n'};
}

using Word = QByteArray;
using Chunk = std::pair<char*, size_t>;

}
}
