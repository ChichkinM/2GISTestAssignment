/*
 * \file Domain.h
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#pragma once

#include <QObject>
#include <QUrl>
#include <parser/Domain.h>

namespace doublegis::model {

class Domain : public QObject
{
Q_OBJECT
    Q_PROPERTY(QUrl url MEMBER url NOTIFY urlChanged)

public:
    Domain(parser::Domain &parser, QObject *parent) noexcept;

public slots:
    void run() noexcept;

signals:
    void urlChanged();

private:
    QUrl url;
    parser::Domain &parser;
};

}
