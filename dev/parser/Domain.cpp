/*
 * \file Domain.cpp
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#include "Domain.h"
#include <QFile>
#include <QDebug>
#include <iostream>
#include <QThread>
#include <QUrl>
#include <QDataStream>
#include <QTimer>

#include "Types.h"
#include "ChunkParser.h"


namespace doublegis {
namespace parser {

namespace {
size_t
findFirstDelimeter(size_t current, size_t end, char *data)
{
    while (current != end) {
        auto currentChar = *(data + current);// data.at(current);
//        auto currentChar = *(data.data() + current);
        auto found = std::find(constants::separators.begin(),
                               constants::separators.end(), currentChar);
        if (found != constants::separators.end()) {
            return current;
        }
        ++current;
    }
    return end;
}
}

Domain::Domain(QObject *parent) noexcept
        : QObject(parent),
          pool(new QThreadPool(this)),
          statistic(new Statistic(this))
{
    auto availableThreads = QThread::idealThreadCount();
    pool->setMaxThreadCount(availableThreads - 1);
}

void Domain::invokeRun(const QUrl &source) noexcept
{
    QMetaObject::invokeMethod(
            this, "run",
            Qt::AutoConnection,
            Q_ARG(const QUrl &, source)
    );
}

const Statistic &Domain::getStatistic() const noexcept
{
    return *statistic;
}

quint8 Domain::getThreadsCount() const noexcept
{
    return pool->maxThreadCount();
}

void Domain::run(const QUrl &source) noexcept
{
    auto file = new QFile(source.path());
    if (!file->exists()) {
        qDebug() << "file not exist" << source.path();
        return;
    }

    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "open error";
        return;
    }

    auto memory = file->map(0, file->size());
    auto fileSize = file->size();
    if (fileSize < 0) {
        return;
    }
    uint64_t chunkSize = fileSize / getThreadsCount();
    qDebug() << "threads:" << getThreadsCount();
    qDebug() << "fileSize:" << fileSize;
    qDebug() << "blockSize:" << chunkSize;

    size_t currentIdx = 0;
    size_t endIdx = fileSize;
    int i = 0;

    emit fileSizeChanged(fileSize);
    statistic->run(fileSize);

    while (currentIdx != endIdx) {
        size_t length = chunkSize;
        if (currentIdx + length > endIdx) {
            length = endIdx - currentIdx;
        } else {
            length = findFirstDelimeter(currentIdx + length, endIdx,
                                        (char *) memory) - currentIdx;
        }


        auto chunk = std::make_pair((char *) memory + currentIdx, length);
        auto parser = new ChunkParser(std::move(chunk), i++, *statistic);
        pool->start(parser);

        currentIdx = currentIdx + length;
    }

    pool->waitForDone();
    for (const auto &s : statistic->fullStatistic) {
        qDebug() << s.first << s.second;
    }

    statistic->clear();
    file->unmap(memory);
    file->close();
}

}
}
