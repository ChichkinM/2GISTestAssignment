/*
 * \file Reader.h
 * \author : Chichkin M.A.
 * \date : 14.08.2021
 */

#pragma once

#include <QUrl>
#include <QFile>
#include "Types.h"

namespace doublegis {
namespace parser {

class Reader : public QObject
{
    Q_OBJECT

public:
    explicit Reader(const QUrl &url, QObject * parent) noexcept(false);
    OptChunk invokeReadNextChunk() noexcept;

    quint64 getFileSize() const noexcept;

private slots:
    OptChunk readNextChunk() noexcept;

private:
    size_t findFirsSeparator(size_t current) const noexcept;
    void close() noexcept;

private:
    QFile file;
    char *fileMemory;

    size_t endIndex;
    size_t currentIndex;
};

}
}
