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
    connect(&parser.getStatistic(), &parser::Statistic::changed,
            this, &Domain::onStatisticUpdate);
    connect(&parser, &parser::Domain::fileSizeChanged,
            this, &Domain::onFileSizeChanged);
    connect(&parser, &parser::Domain::finished,
            this, &Domain::onFinished);
}

void Domain::run() noexcept
{
    wordsPrimaryModel->clear();
    resetStatuses();

    begin = QDateTime::currentDateTime();
    emit beginChanged();

    status = Running;
    emit statusChanged();

    parser.invokeRun(url);
}

void Domain::onStatisticUpdate(doublegis::StatisticUpdatePtr update) noexcept
{
    std::visit(UpdateVisitor{*this}, std::move(*update));
}

void Domain::UpdateVisitor::operator()(doublegis::MostCommonWordsStorage newStorage) noexcept
{
    self.wordsPrimaryModel->update(std::move(newStorage));
}

QString Domain::getFileName() const noexcept
{
    return url.fileName();
}

void Domain::onFinished() noexcept
{
    if (status != Done) {
        end = QDateTime::currentDateTime();
        emit endChanged();

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

void Domain::UpdateVisitor::operator()(quint64 newProcessedData) noexcept
{
    if (self.processedData != newProcessedData) {
        self.processedData = newProcessedData;
        emit self.processedDataChanged();
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

        resetStatuses();
    }
}

/*TODO можно завести объект сессии,
 * в пределах которого происходила бы одна обработка файла
 * */
void Domain::resetStatuses() noexcept
{
    status = NotRunning;
    emit statusChanged();

    processedData = 0;
    emit processedDataChanged();

    fullSize = 0;
    emit fullSizeChanged();
}

}