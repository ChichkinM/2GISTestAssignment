/*
 * \file Domain.h
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#pragma once

#include <QObject>
#include <QThreadPool>
#include "Statistic.h"

namespace doublegis {
namespace parser {

class Domain : public QObject
{
Q_OBJECT
public:
    explicit Domain(QObject *parent) noexcept;
    const Statistic &getStatistic() const noexcept;

    void invokeRun(const QUrl &source) noexcept;

signals:
    void fileSizeChanged(quint64 size);

private slots:
    void run(const QUrl &source) noexcept;

private:
    quint8 getThreadsCount() const noexcept;

private:
    QThreadPool *const pool;
    Statistic *const statistic;
};

}
}
