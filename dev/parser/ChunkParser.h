/*
 * \file ChunkParser.h
 * \author : Chichkin M.A.
 * \date : 12.08.2021
 */

#pragma once

#include <QObject>
#include "Types.h"
#include "Statistic.h"
#include "Reader.h"

namespace doublegis {
namespace parser {

class ChunkParser : public QObject
{
    Q_OBJECT
public:
    ChunkParser(int index, Reader &reader, Statistic &statistic) noexcept;

public slots:
    void run();

signals:
    void finished();

private:

    void processChunk(Chunk & chunk) noexcept;
    void processProgress(size_t newProgress) noexcept;
    void postProgress(size_t newProgress) noexcept;

    void processWord(Chunk & chunk, size_t beginIndex, size_t length) noexcept;
    void postLocalStatistic() noexcept;

private:
    int parserIndex;
    Statistic &statistic;
    Reader &reader;

    size_t prevPostedIndex;
    StatisticStorage localStatistic;
    size_t wordsInLocalStatistic;
};

}
}
