/*
 * \file Statistic.cpp
 * \author : Chichkin M.A.
 * \date : 12.08.2021
 */

#include "Statistic.h"
#include <QDebug>
#include <mutex>
#include <cassert>
#include "Utils.h"

namespace doublegis {
namespace parser {

Statistic::Statistic(QObject *parent) noexcept
        : QObject(parent),
          processedDataSize(0),
          fullDataSize(0),
          prevProgressEmited(0)
{
}

void Statistic::push(StatisticStorage &&words) noexcept
{
    std::scoped_lock lock(mutex);
    bool mostCommonWordsUpdated(false);

    for (auto &&word : words) {
        auto found = fullStatistic.find(word.first);
        if (found != fullStatistic.end()) {
            found->second += word.second;
            mostCommonWordsUpdated |= processUpdate(found);
        } else {
            auto inserted = fullStatistic.insert(std::move(word));
            assert(inserted.second && "insert error");
            mostCommonWordsUpdated |= processUpdate(inserted.first);
        }
    }

    if(mostCommonWordsUpdated) {
        emit statisticChanged(mostCommon);
    }
}

bool Statistic::processUpdate(StatisticStorage::iterator entryIt) noexcept
{
    if (mostCommon.size() >= constants::mostCommonWordsLimit &&
        mostCommon.begin()->first > entryIt->second) {
        return false;
    }

    for (auto it = mostCommon.begin(); it != mostCommon.end(); it++) {
        if (it->second == entryIt->first) {
            mostCommon.erase(it);
            break;
        }
    }

    mostCommon.insert({entryIt->second, entryIt->first});

    uint8_t keysCount(0);
    for (auto it = mostCommon.begin(); it != mostCommon.end();
         it = mostCommon.upper_bound(it->first)) {
        ++keysCount;
    }

    if (keysCount > constants::mostCommonWordsLimit) {
        mostCommon.erase(mostCommon.begin());
    }

    return true;
}

void Statistic::update(size_t processedDataSize) noexcept
{
    std::scoped_lock lock(mutex2);
    Statistic::processedDataSize += processedDataSize;
    auto newProgress = ((double) Statistic::processedDataSize / (double) fullDataSize) * 100;

    if (newProgress - prevProgressEmited >= 1) {
        emit processedDataChanged(Statistic::processedDataSize);
        prevProgressEmited = newProgress;
    }
}

void Statistic::run(size_t fullDataSize) noexcept
{
    clear();
    Statistic::fullDataSize = fullDataSize;
}

void Statistic::clear() noexcept
{
    mostCommon.clear();
    fullStatistic.clear();
    Statistic::fullDataSize = 0;
    processedDataSize = 0;
    prevProgressEmited = 0;
}

}
}