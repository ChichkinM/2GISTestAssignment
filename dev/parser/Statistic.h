/*
 * \file Statistic.h
 * \author : Chichkin M.A.
 * \date : 12.08.2021
 */

#pragma once

#include <map>
#include <QMutex>
#include <QObject>
#include "Types.h"

namespace doublegis {
namespace parser {

class Statistic : public QObject
{
    Q_OBJECT
public:
    explicit Statistic(QObject * parent) noexcept;

    void run(size_t fullDataSize) noexcept;
    void push(StatisticStorage && words) noexcept;
    void update(size_t processedDataSize) noexcept;
    void clear() noexcept;

signals:
    void changed(doublegis::StatisticUpdatePtr update);

private:
    bool processUpdate(StatisticStorage::iterator entryIt) noexcept;

public:
    QMutex mutex;
    StatisticStorage fullStatistic;
    MostCommonWordsStorage mostCommon;

    QMutex mutex2;
    size_t processedDataSize;

    size_t fullDataSize;
    size_t prevProgressEmited;
};

}
}
