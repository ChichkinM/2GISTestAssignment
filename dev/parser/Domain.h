/*
 * \file Domain.h
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#pragma once

#include <QObject>

namespace doublegis::parser {

class Domain : public QObject
{
Q_OBJECT
public:
    explicit Domain(QObject *parent) noexcept;

    void run(const QUrl &source) noexcept;
};

}
