/*
 * \file Domain.h
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#pragma once

#include <QObject>
#include <QUrl>
#include <parser/Domain.h>

namespace doublegis {
namespace model {

class Domain : public QObject
{
Q_OBJECT
    Q_PROPERTY(QUrl url MEMBER url NOTIFY urlChanged)
    Q_PROPERTY(quint64 processedSize MEMBER processedData NOTIFY processedDataChanged)
    Q_PROPERTY(quint64 fullSize MEMBER fullSize NOTIFY fullSizeChanged)

public:
    Domain(parser::Domain &parser, QObject *parent) noexcept;

public slots:
    void run() noexcept;

signals:
    void urlChanged();
    void processedDataChanged();
    void fullSizeChanged();

private:
    QUrl url;
    quint64 processedData;
    quint64 fullSize;

    parser::Domain &parser;
};

}
}
