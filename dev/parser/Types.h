/*
 * \file Types.h
 * \author : Chichkin M.A.
 * \date : 12.08.2021
 */

#pragma once

#include <array>
#include <map>
#include <QByteArray>

namespace doublegis {
namespace parser {

namespace constants {
const std::array<char, 2> separators{' ', '\n'};
const uint8_t mostCommonWordsLimit = 15;
}

using Word = QByteArray;
using Chunk = std::pair<char*, size_t>;
using StatisticStorage = std::map<Word, size_t>;
using MostCommonWordsStorage = std::multimap< size_t, QString>;

}
}
