/*
 * \file Domain.cpp
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#include "Domain.h"
#include <QDebug>

#include "Types.h"
#include "ChunkParser.h"
#include "Reader.h"


namespace doublegis {
namespace parser {

Domain::Domain(QObject *parent) noexcept
        : QObject(parent),
          threadsCount(QThread::idealThreadCount() - 2),
          statistic(new Statistic(this))
{
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
    return threadsCount;
}

void Domain::run(const QUrl &source) noexcept
{
    assert(!reader && "file reader is already created");
    try {
        reader = std::make_unique<Reader>(source, nullptr);
    }
    catch (const std::logic_error &e) {
        qDebug() << "Reader error" << e.what();
        emit finished();
        return;
    }

    emit fileSizeChanged(reader->getFileSize());
    statistic->run(reader->getFileSize());

    for (auto i = 0; i < getThreadsCount();) {
        auto thread = std::make_shared<QThread>(nullptr);
        threads.insert(thread);

        auto parser = new ChunkParser(i, *reader, *statistic);
        parser->moveToThread(thread.get());
        thread->start();

        connect(thread.get(), &QThread::started,
                parser, &ChunkParser::run);
        connect(parser, &ChunkParser::finished,
                this, [this, thread]() {
                    onThreadFinished(thread);
                });
        ++i;
    }
}

void Domain::onThreadFinished(const QThreadPtr &thread) noexcept
{
    assert(thread && "thread is nullptr");

    thread->quit();
    thread->wait();
    threads.erase(thread);

    if (!threads.empty()) {
        return;
    }

    statistic->clear();
    reader.reset();
    emit finished();
}

}
}
