/*
 * \file Statistic.cpp
 * \author : Chichkin M.A.
 * \date : 12.08.2021
 */

#include "Statistic.h"
#include <QDebug>
#include <mutex>

namespace doublegis {
namespace parser {

Statistic::Statistic(QObject *parent) noexcept
        : QObject(parent)
{

}

void Statistic::push(Word word) noexcept
{
    std::scoped_lock lock(mutex);

    auto found = fullStatistic.find(word);
    if (found != fullStatistic.end()) {
        ++found->second;
    } else {
        fullStatistic.insert({std::move(word), 1});
    }
}

void Statistic::update(size_t processedDataSize) noexcept
{
    std::scoped_lock lock(mutex2);
    Statistic::processedDataSize += processedDataSize;
    auto newProgress = ((double) Statistic::processedDataSize / (double) fullDataSize) * 100;
    if( newProgress - prevProgressEmited >= 1) {
        emit processedDataChanged(Statistic::processedDataSize);
        qDebug() << newProgress << "%";

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
    fullStatistic.clear();
    Statistic::fullDataSize = 0;
    processedDataSize = 0;
    prevProgressEmited = 0;
}

}
}