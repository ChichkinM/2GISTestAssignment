/*
 * \file Types.h
 * \author : Chichkin M.A.
 * \date : 12.08.2021
 */

#pragma once

#include <array>
#include <map>
#include <optional>
#include <set>
#include <variant>
#include <memory>

#include <QByteArray>
#include <QString>

namespace doublegis {

namespace constants {
const std::array<char, 2> separators{' ', '\n'};
const uint8_t mostCommonWordsLimit = 15;
const uint32_t chunkSize = 30000;
}

using Word = QByteArray;
using Chunk = QByteArray;
using OptChunk = std::optional<Chunk>;
using StatisticStorage = std::map<Word, size_t>;

struct WordAndCount
{
    QString word;
    quint64 count;

    /* Используется для бинарного поиска.
     * Сперва сортирует по счетчику (от большего к меньшему).
     * При равных счетчиках сортирует лексографически.
     * */
    bool operator<(const WordAndCount &rhs) const noexcept;
};
using MostCommonWordsStorage = std::set<WordAndCount>;
using ProcessedData = quint64;

using StatisticUpdate = std::variant<MostCommonWordsStorage, ProcessedData>;
using StatisticUpdatePtr = std::shared_ptr<StatisticUpdate>;

}
