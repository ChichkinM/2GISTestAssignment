/*
 * \file ChunkParser.h
 * \author : Chichkin M.A.
 * \date : 12.08.2021
 */

#pragma once

#include <QRunnable>
#include "Types.h"
#include "Statistic.h"
#include <QDebug>

namespace doublegis {
namespace parser {

class ChunkParser : public QRunnable
{
public:
    ChunkParser(Chunk chunk, int index, Statistic & statistic);

private:
    void run() override;

private:
    int parserIndex;
    Chunk chunk;
    Statistic & statistic;
};

}
}
