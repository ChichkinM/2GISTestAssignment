/*
 * \file ChunkParser.cpp
 * \author : Chichkin M.A.
 * \date : 12.08.2021
 */

#include "ChunkParser.h"
#include <QDebug>
#include <QDataStream>
#include <iostream>
#include <cassert>
#include "Utils.h"

namespace doublegis {
namespace parser {

ChunkParser::ChunkParser(Chunk chunk, int index, Statistic &statistic)
        : parserIndex(index), chunk(std::move(chunk)), statistic(statistic),
          prevPostedIndex(0), wordsInLocalStatistic(0)
{
}

void ChunkParser::run()
{
    auto beginWordIdx = 0;
    for (size_t i = 0; i < chunk.second; i++) {
        processProgress(i);

        if (!utils::isSeparator(*((char *) chunk.first + i))) {
            continue;
        }

        if (beginWordIdx != i) {
            processWord(beginWordIdx, i - beginWordIdx);
        }

        beginWordIdx = i + 1;
    }

    if (beginWordIdx != chunk.second) {
        processWord(beginWordIdx, chunk.second - beginWordIdx);
    }

    postLocalStatistic();
    postProgress(chunk.second);
}

void ChunkParser::processWord(size_t beginIndex, size_t length) noexcept
{
    auto word = Word::fromRawData(chunk.first + beginIndex, length);
    auto found = localStatistic.find(word);
    if (found != localStatistic.end()) {
        ++found->second;
    } else {
        localStatistic.insert({std::move(word), 1});
    }
    ++wordsInLocalStatistic;

    if (wordsInLocalStatistic >= 500000) {
        postLocalStatistic();
    }
}

void ChunkParser::postLocalStatistic() noexcept
{
    if (!localStatistic.empty()) {
        statistic.push(std::move(localStatistic));
        localStatistic.clear();
        wordsInLocalStatistic = 0;
    }
}

void ChunkParser::postProgress(size_t newProgress) noexcept
{
    statistic.update(newProgress - prevPostedIndex);
    prevPostedIndex = newProgress;
}

void ChunkParser::processProgress(size_t newProgress) noexcept
{
    if (newProgress % 1000000 == 0) {
        postProgress(newProgress);
    }
}

}
}