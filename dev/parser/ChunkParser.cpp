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

namespace doublegis {
namespace parser {

ChunkParser::ChunkParser(Chunk chunk, int index, Statistic & statistic)
        : parserIndex(index), chunk(std::move(chunk)), statistic(statistic)
{
}

void ChunkParser::run()
{
    auto prevPushedIndex = 0;
    auto beginWordIdx = 0;
    for(size_t i = 0; i < chunk.second; i++) {
        auto found = std::find(constants::separators.begin(),
                               constants::separators.end(), *((char*)chunk.first + i));
        if (found == constants::separators.end()) {
            continue;
        }

        if (beginWordIdx != i) {
            static int skipper = 0;
            skipper++;
            auto word = Word::fromRawData(chunk.first + beginWordIdx, i - beginWordIdx);
//            statistic.push(std::move(word));
            if( skipper % 1000 == 0 ) {
                statistic.update(i - prevPushedIndex);
                prevPushedIndex = i;
            }
        }

        beginWordIdx = i + 1;
    }

    if(beginWordIdx != chunk.second)
    {
        auto word = Word::fromRawData(chunk.first + beginWordIdx, chunk.second - beginWordIdx);
//        statistic.push(std::move(word));
        statistic.update(chunk.second - prevPushedIndex);
    }
}

}
}