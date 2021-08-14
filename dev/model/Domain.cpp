/*
 * \file Domain.cpp
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#include "Domain.h"

#include <QDebug>

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
            this, [this](quint64 newProcessedData) {
                if (processedData != newProcessedData) {
                    processedData = newProcessedData;
                    emit processedDataChanged();
                }
            });

    connect(&parser.getStatistic(), &parser::Statistic::statisticChanged,
            this, &Domain::onNewStatistic);

    connect(&parser, &parser::Domain::fileSizeChanged,
            this, [this](quint64 newFullSize) {
                if (fullSize != newFullSize) {
                    fullSize = newFullSize;
                    emit fullSizeChanged();
                }
            });
    connect(&parser, &parser::Domain::finished,
            this, [this]() {
                if (status != Done) {
                    status = Done;
                    emit statusChanged();
                }
            });
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

}