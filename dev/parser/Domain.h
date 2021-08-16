/*
 * \file Domain.h
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#pragma once

#include <QObject>
#include <QThread>
#include "Statistic.h"
#include "Reader.h"

namespace doublegis {
namespace parser {

class Domain : public QObject
{
Q_OBJECT
using QThreadPtr = std::shared_ptr<QThread>;

public:
    explicit Domain(QObject *parent) noexcept;
    const Statistic &getStatistic() const noexcept;

    void invokeRun(const QUrl &source) noexcept;

signals:
    void fileSizeChanged(quint64 size);
    void finished();

private slots:
    void run(const QUrl &source) noexcept;
    void onThreadFinished(const QThreadPtr & thread) noexcept;

private:
    quint8 getThreadsCount() const noexcept;

private:
    quint8 threadsCount;
    std::set<QThreadPtr> threads;
    Statistic *const statistic;
    std::unique_ptr<Reader> reader;
};

}
}
