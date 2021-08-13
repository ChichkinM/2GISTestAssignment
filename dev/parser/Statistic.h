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
    void push(Word word) noexcept;
    void update(size_t processedDataSize) noexcept;
    void clear() noexcept;

signals:
    void processedDataChanged(quint64 data);

public:
    QMutex mutex;
    std::map<Word, uint64_t> fullStatistic;

    size_t fullDataSize;

    QMutex mutex2;
    size_t processedDataSize;
    size_t prevProgressEmited;
};

}
}
