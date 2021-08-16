/*
 * \file ChunkParser.cpp
 * \author : Chichkin M.A.
 * \date : 12.08.2021
 */

#include "ChunkParser.h"
#include "Utils.h"

namespace doublegis {
namespace parser {

ChunkParser::ChunkParser(int index, Reader &reader, Statistic &statistic) noexcept
        : QObject(nullptr),
          parserIndex(index),
          statistic(statistic), reader(reader),
          prevPostedIndex(0), wordsInLocalStatistic(0)
{
}

void ChunkParser::run()
{
    while (auto expectedChunk = reader.invokeReadNextChunk()) {
        processChunk( *expectedChunk );
    }
    emit finished();
}

void ChunkParser::processChunk(Chunk & chunk) noexcept
{
    prevPostedIndex = 0;
    wordsInLocalStatistic = 0;
    localStatistic.clear();

    auto beginWordIdx = 0;
    for (size_t i = 0; i < chunk.size(); i++) {
        processProgress(i);

        if (!utils::isSeparator(chunk.at(i))) {
            continue;
        }

        if (beginWordIdx != i) {
            processWord(chunk, beginWordIdx, i - beginWordIdx);
        }

        beginWordIdx = i + 1;
    }

    if (beginWordIdx != chunk.size()) {
        processWord(chunk, beginWordIdx, chunk.size() - beginWordIdx);
    }

    postLocalStatistic();
    postProgress(chunk.size());
}

void ChunkParser::processWord(Chunk & chunk, size_t beginIndex, size_t length) noexcept
{
    auto word = chunk.mid(beginIndex, length);
    auto found = localStatistic.find(word);
    if (found != localStatistic.end()) {
        ++found->second;
    } else {
        localStatistic.insert({std::move(word), 1});
    }
    ++wordsInLocalStatistic;

    if (wordsInLocalStatistic >= 50000) {
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