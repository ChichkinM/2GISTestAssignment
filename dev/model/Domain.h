/*
 * \file Domain.h
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#pragma once

#include <QObject>
#include <QUrl>
#include <parser/Domain.h>

#include "WordsPrimaryModel.h"
#include "WordsProxyModel.h"

namespace doublegis {
namespace model {

class Domain : public QObject
{
Q_OBJECT
    Q_PROPERTY(doublegis::model::WordsPrimaryModel *primary MEMBER wordsPrimaryModel CONSTANT)
    Q_PROPERTY(doublegis::model::WordsProxyModel *proxy MEMBER wordsProxyModel CONSTANT)

    Q_PROPERTY(doublegis::model::Domain::Status status MEMBER status NOTIFY statusChanged)
    Q_PROPERTY(QUrl url MEMBER url NOTIFY urlChanged)
    Q_PROPERTY(QString fileName READ getFileName NOTIFY urlChanged)
    Q_PROPERTY(quint64 processedSize MEMBER processedData NOTIFY processedDataChanged)
    Q_PROPERTY(quint64 fullSize MEMBER fullSize NOTIFY fullSizeChanged)

public:
    enum Status
    {
        NotRunning = 0,
        Running,
        Done
    };
    Q_ENUM(Status)

public:
    Domain(parser::Domain &parser, QObject *parent) noexcept;

public slots:
    void run() noexcept;

private slots:
    void onNewStatistic(doublegis::parser::MostCommonWordsStorage newStorage) noexcept;

signals:
    void urlChanged();
    void processedDataChanged();
    void fullSizeChanged();
    void statusChanged();

private:
    QString getFileName() const noexcept;

private:
    WordsPrimaryModel *const wordsPrimaryModel;
    WordsProxyModel *const wordsProxyModel;

    Status status;
    QUrl url;
    quint64 processedData;
    quint64 fullSize;

    parser::Domain &parser;
};

}
}
