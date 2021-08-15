/*
 * \file Domain.cpp
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#include "Domain.h"

namespace doublegis::model {

Domain::Domain(parser::Domain &parser, QObject *parent) noexcept
        : QObject(parent),
          wordsPrimaryModel(new WordsPrimaryModel(this)),
          wordsProxyModel(new WordsProxyModel(wordsPrimaryModel, this)),
          status(NotRunning),
          processedData(0),
          parser(parser)
{
    connect(&parser.getStatistic(), &parser::Statistic::processedDataChanged,
            this, &Domain::onProcessedDataChanged);
    connect(&parser.getStatistic(), &parser::Statistic::statisticChanged,
            this, &Domain::onNewStatistic);
    connect(&parser, &parser::Domain::fileSizeChanged,
            this, &Domain::onFileSizeChanged);
    connect(&parser, &parser::Domain::finished,
            this, &Domain::onFinished);
}

void Domain::run() noexcept
{
    wordsPrimaryModel->clear();

    status = Running;
    emit statusChanged();

    parser.invokeRun(url);
}

void Domain::onNewStatistic(doublegis::parser::MostCommonWordsStorage newStorage) noexcept
{
    wordsPrimaryModel->update(std::move(newStorage));
}

QString Domain::getFileName() const noexcept
{
    return url.fileName();
}

void Domain::onFinished() noexcept
{
    if (status != Done) {
        status = Done;
        emit statusChanged();
    }
}

void Domain::onFileSizeChanged(quint64 newFullSize) noexcept
{
    if (fullSize != newFullSize) {
        fullSize = newFullSize;
        emit fullSizeChanged();
    }
}

void Domain::onProcessedDataChanged(quint64 newProcessedData) noexcept
{
    if (processedData != newProcessedData) {
        processedData = newProcessedData;
        emit processedDataChanged();
    }
}

QUrl Domain::getUrl() const noexcept
{
    return url;
}

void Domain::setUrl(QUrl newUrl) noexcept
{
    if (url != newUrl) {
        url = newUrl;
        emit urlChanged();

        status = NotRunning;
        emit statusChanged();

        processedData = 0;
        emit processedDataChanged();

        fullSize = 0;
        emit fullSizeChanged();
    }
}

}