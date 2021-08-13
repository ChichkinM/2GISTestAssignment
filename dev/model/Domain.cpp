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
    connect(&parser, &parser::Domain::fileSizeChanged,
            this, [this](quint64 newFullSize) {
                if (fullSize != newFullSize) {
                    fullSize = newFullSize;
                    emit fullSizeChanged();
                }
            });
}

void Domain::run() noexcept
{
    parser.invokeRun(url);
}

}