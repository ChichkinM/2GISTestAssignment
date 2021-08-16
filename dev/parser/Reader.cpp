/*
 * \file Reader.cpp
 * \author : Chichkin M.A.
 * \date : 14.08.2021
 */

#include "Reader.h"
#include "Utils.h"

namespace doublegis {
namespace parser {

Reader::Reader(const QUrl &url, QObject * parent) noexcept(false)
        : QObject(parent),
        file(QFile(url.path())),
          fileMemory(nullptr),
          endIndex(file.size()),
          currentIndex(0)
{
    if (!file.exists()) {
        throw std::logic_error("file not exist");
    }

    if (!file.open(QIODevice::ReadOnly)) {
        throw std::logic_error("failed to open file");
    }

    fileMemory = (char *) file.map(0, file.size());
}

OptChunk Reader::readNextChunk() noexcept
{
    if(!fileMemory) {
        return {};
    }

    if (currentIndex == endIndex) {
        close();
        return {};
    }

    size_t length = constants::chunkSize;
    if (currentIndex + length > endIndex) {
        length = endIndex - currentIndex;
    } else {
        length = findFirsSeparator(currentIndex + length) - currentIndex;
    }

    auto tmpCurrentIndex = currentIndex;
    currentIndex += length;
    return QByteArray(fileMemory + tmpCurrentIndex, length);
}

OptChunk Reader::invokeReadNextChunk() noexcept
{
    OptChunk retType;
    QMetaObject::invokeMethod(
            this, "readNextChunk",
            Qt::BlockingQueuedConnection,
            Q_RETURN_ARG(OptChunk, retType)
    );
    return retType;
}

size_t Reader::findFirsSeparator(size_t current) const noexcept
{
    while (current != endIndex) {
        auto currentChar = *(fileMemory + current);
        if( utils::isSeparator(currentChar) ) {
            return current;
        }
        ++current;
    }
    return endIndex;
}

quint64 Reader::getFileSize() const noexcept
{
    return endIndex;
}

void Reader::close() noexcept
{
    file.unmap((uchar *) fileMemory);
    file.close();
    fileMemory = nullptr;
}

}
}